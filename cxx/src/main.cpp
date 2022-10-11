#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <any>

#include "type-wrapper.hpp"
using namespace cpp::base;

#include "nlohmann/json.hpp"
using json = nlohmann::json;

std::map<std::string, std::function<std::string(TypeWrapper &)>> flist;

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

template <typename T>
std::string convertAdapter(std::string data)
{
    auto j = json::parse(data);
    auto functionName = j["function"].get<std::string>();
    TypeWrapper functionParam = j["param"].get<T>();
    return flist[functionName](functionParam);
}

int main()
{
    flist["test1"] = &test1;
    flist["test2"] = &test2;

    json j{
        {"function", "test1"},
        {"param", true},
    };

    auto functionReturn = convertAdapter<bool>(j.dump());
    std::cout << "[Main] Returned Value: " << functionReturn << std::endl;
}
