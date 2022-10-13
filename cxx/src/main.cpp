#include <string>
#include <iostream>
#include <vector>
#include <functional>

#include "type-wrapper.hpp"
using namespace cpp::base;

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// MAPPING DATA

template <typename T>
std::string convertAdapter(std::string data);

struct MappingItem
{
    std::string name;
    std::function<const std::string(const std::string &)> executor;
    std::function<std::string(TypeWrapper &)> target;

    MappingItem(std::string &&name, std::function<std::string(TypeWrapper &)> &&target, std::function<const std::string(const std::string &)> &&executor)
    {
        this->name = std::move(name);
        this->target = std::move(target);
        this->executor = std::move(executor);
    }

    template <typename T>
    static MappingItem create(std::string &&name, std::function<std::string(TypeWrapper &)> &&target)
    {
        return MappingItem{
            std::move(name),
            std::move(target),
            [&target](const std::string &data)
            {
                return convertAdapter<T>(data);
            },
        };
    }
};

auto mapping = std::vector<MappingItem>{};

// ADAPTER FUNCTION

template <typename T>
std::string convertAdapter(std::string data)
{
    auto j = json::parse(data);

    std::string functionName = j["function"].get<std::string>();
    TypeWrapper functionParam = j["param"].get<T>();

    auto mappingItem = std::find_if(mapping.begin(), mapping.end(), [&functionName](const MappingItem &item)
                                    { return item.name == functionName; });

    if (mappingItem != mapping.end())
    {
        return mappingItem->target(functionParam);
    }

    return "";
}

// EXECUTOR

std::string executor(std::string data)
{
    auto j = json::parse(data);

    std::string functionName = j["function"].get<std::string>();

    auto mappingItem = std::find_if(mapping.begin(), mapping.end(), [&functionName](const MappingItem &item)
                                    { return item.name == functionName; });

    if (mappingItem != mapping.end())
    {
        return mappingItem->executor(data);
    }

    return "";
}

// REAL FUNCTIONS

std::string test1(TypeWrapper &value)
{
    auto rawValue = value.get<bool>();
    std::cout << "[Test1] Received Value: " << std::to_string(rawValue) << std::endl;

    return "{}";
}

std::string test2(TypeWrapper &value)
{
    auto rawValue = value.get<std::string>();
    std::cout << "[Test2] Received Value: " << rawValue << std::endl;

    return "{}";
}

// MAIN

int main()
{
    mapping.push_back(MappingItem::create<bool>("test1", &test1));
    mapping.push_back(MappingItem::create<std::string>("test2", &test2));

    {
        // test one: bool
        json j{
            {"function", "test1"},
            {"param", true},
        };

        auto jstr = j.dump();

        auto functionReturn = executor(jstr);
        std::cout << "[Main1] Returned Value: " << functionReturn << std::endl;
    }

    {
        // test two: string
        json j{
            {"function", "test2"},
            {"param", "my name"},
        };

        auto jstr = j.dump();

        auto functionReturn = executor(jstr);
        std::cout << "[Main2] Returned Value: " << functionReturn << std::endl;
    }
}
