#pragma once

#include <memory>
#include <type_traits>
#include <utility>

namespace cpp
{
    namespace base
    {

        class TypeWrapper
        {
        public:
            TypeWrapper() noexcept : storage_(nullptr, noopDeleter) {}
            TypeWrapper(TypeWrapper &&) noexcept = default;
            TypeWrapper &operator=(TypeWrapper &&) noexcept = default;

            template <typename T> // NOLINTNEXTLINE misc-forwarding-reference-overload
            TypeWrapper(T &&value) noexcept
                : storage_(new std::decay_t<T>(std::forward<T>(value)), castDeleter<std::decay_t<T>>)
            {
                static_assert(!std::is_same<TypeWrapper, std::decay_t<T>>::value, "TypeWrapper must not wrap itself.");
            }

            bool hasValue() const noexcept { return static_cast<bool>(storage_); }

            template <typename T>
            T &get() noexcept
            { // NOLINTNEXTLINE cppcoreguidelines-pro-type-reinterpret-cast
                return *reinterpret_cast<T *>(storage_.get());
            }

        private:
            template <typename T>
            static void castDeleter(void *ptr) noexcept
            {
                delete reinterpret_cast<T *>(ptr); // NOLINT cppcoreguidelines-pro-type-reinterpret-cast
            }
            static void noopDeleter(void *) noexcept {}

            using storage_t = std::unique_ptr<void, void (*)(void *)>;
            storage_t storage_;
        };

    } // namespace base
} // namespace cpp
