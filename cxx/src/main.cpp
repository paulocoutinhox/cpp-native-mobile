#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <any>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// MAPPING DATA

template <typename... Ts>
std::string convertAdapter(std::string data);

struct MappingItem
{
    std::string name;
    std::function<const std::string(const std::string &)> executor;
    std::function<std::string(std::map<std::string, std::any> &)> target;

    MappingItem(std::string &&name, std::function<std::string(std::map<std::string, std::any> &)> &&target, std::function<const std::string(const std::string &)> &&executor)
    {
        this->name = std::move(name);
        this->target = std::move(target);
        this->executor = std::move(executor);
    }

    template <typename... Ts>
    static MappingItem create(std::string &&name, std::function<std::string(std::map<std::string, std::any> &)> &&target)
    {
        return MappingItem{
            std::move(name),
            std::move(target),
            [](const std::string &data)
            {
                return convertAdapter<Ts...>(data);
            },
        };
    }
};

auto mapping = std::vector<MappingItem>{};

// ADAPTER FUNCTION

template <typename... Ts>
std::string convertAdapter(std::string data)
{
    auto j = json::parse(data);

    std::string functionName = j["function"].get<std::string>();

    std::map<std::string, std::any> params = {};

    auto functionParams = j["params"];
    auto paramsSize = j["params"].size();
    auto paramCount = 0;

    (
        [&]()
        {
            auto paramName = functionParams[paramCount]["name"].get<std::string>();
            std::any paramValue = functionParams[paramCount]["value"].get<Ts>();

            params[paramName] = paramValue;
            paramCount++;
        }(),
        ...);

    auto mappingItem = std::find_if(mapping.begin(), mapping.end(), [&functionName](const MappingItem &item)
                                    { return item.name == functionName; });

    if (mappingItem != mapping.end())
    {
        return mappingItem->target(params);
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

std::string test1(std::map<std::string, std::any> &values)
{
    auto rawValue1 = std::any_cast<bool>(values["p1"]);
    std::cout << "[Test1] Received Value 1: " << std::to_string(rawValue1) << std::endl;

    auto rawValue2 = std::any_cast<std::string>(values["p2"]);
    std::cout << "[Test1] Received Value 2: " << rawValue2 << std::endl;

    return "{}";
}

std::string test2(std::map<std::string, std::any> &values)
{
    auto rawValue1 = std::any_cast<std::string>(values["p1"]);
    std::cout << "[Test2] Received Value 1: " << rawValue1 << std::endl;

    auto rawValue2 = std::any_cast<float_t>(values["p2"]);
    std::cout << "[Test2] Received Value 2: " << std::to_string(rawValue2) << std::endl;

    return "{}";
}

// MAIN

int main()
{
    mapping.push_back(MappingItem::create<bool, std::string>("test1", &test1));
    mapping.push_back(MappingItem::create<std::string, float_t>("test2", &test2));

    {
        // test one: bool
        auto jstr = R"(
        {
            "function": "test1",
            "params": [
                {
                    "name": "p1",
                    "value": true
                },
                {
                    "name": "p2",
                    "value": "my name"
                }
            ]
        }
        )";

        auto functionReturn = executor(jstr);
        std::cout << "[Main1] Returned Value: " << functionReturn << std::endl;
    }

    {
        // test two: string
        auto jstr = R"(
        {
            "function": "test2",
            "params": [
                {
                    "name": "p1",
                    "value": "my name"
                },
                {
                    "name": "p2",
                    "value": 3.14
                }
            ]
        }
        )";

        auto functionReturn = executor(jstr);
        std::cout << "[Main2] Returned Value: " << functionReturn << std::endl;
    }
}
