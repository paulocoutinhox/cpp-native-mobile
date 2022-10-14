#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <any>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// MACRO

#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable), #Variable)
#define MACRO_FUNCTION_TO_STRING(Function) (void(&Function), #Function)
#define MACRO_METHOD_TO_STRING(ClassName, Method) (void(&ClassName::Method), #Method)
#define MACRO_TYPE_TO_STRING(Type) (void(sizeof(Type)), #Type)

// MODELS

class Product
{
public:
    long id;
    std::string name;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Product, id, name)

// MAPPING DATA

template <typename... Ts>
std::string convertAdapter(std::string data);

struct MappingItem
{
    std::string name;
    std::function<const std::string(const std::string &)> executor;
    std::function<std::string(std::map<std::string, std::any> &)> target;
    std::vector<std::string> paramNames;

    MappingItem(std::string &&name, std::function<std::string(std::map<std::string, std::any> &)> &&target, std::function<const std::string(const std::string &)> &&executor, std::vector<std::string> &&paramNames)
    {
        this->name = std::move(name);
        this->target = std::move(target);
        this->executor = std::move(executor);
        this->paramNames = std::move(paramNames);
    }

    template <typename... Ts, typename... Args>
    static MappingItem create(std::string &&name, std::function<std::string(std::map<std::string, std::any> &)> &&target, std::vector<std::string> &&mappingParamNames)
    {
        return MappingItem{
            std::move(name),
            std::move(target),
            [](const std::string &data)
            {
                return convertAdapter<Ts...>(data);
            },
            std::move(mappingParamNames),
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

    // clang-format off
    (
        [&]()
        {
            auto paramName = functionParams[paramCount]["name"].get<std::string>();
            std::any paramValue = functionParams[paramCount]["value"].get<Ts>();

            params[paramName] = paramValue;
            paramCount++;
        }(),...
    );

    auto mappingItem = std::find_if(mapping.begin(), mapping.end(), [&functionName](const MappingItem &item){ return item.name == functionName; });
    // clang-format on

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

    // clang-format off
    auto mappingItem = std::find_if(mapping.begin(), mapping.end(), [&functionName](const MappingItem &item){ return item.name == functionName; });
    // clang-format on

    if (mappingItem != mapping.end())
    {
        return mappingItem->executor(data);
    }

    return "";
}

// GENERATOR

template <typename... Args>
std::string generator(std::string &&name, Args... args)
{
    // clang-format off
    auto mappingItem = std::find_if(mapping.begin(), mapping.end(), [&name](const MappingItem &item){ return item.name == name; });
    // clang-format on

    if (mappingItem != mapping.end())
    {
        json j;
        j["function"] = mappingItem->name;
        j["params"] = json::array();

        int paramCount = 0;

        // clang-format off
        (
            [&]()
            {
                json o;
                o["name"] = mappingItem->paramNames[paramCount];
                o["value"] = args;
                j["params"].push_back(o);

                paramCount++;
            }(),...
        );
        // clang-format on

        return j.dump();
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

std::string test3(std::map<std::string, std::any> &values)
{
    auto rawValue1 = std::any_cast<Product>(values["prod"]);
    std::cout << "[Test3] Received Product: " << rawValue1.id << ", " << rawValue1.name << std::endl;

    return "{}";
}

// TESTS
void libTest1()
{
    // test 1: bool and string
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

void libTest2()
{
    // test 2: string and float
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

void libTest3()
{
    // test 3: generator
    auto jstr = generator("test1", true, "ok");
    std::cout << "[Main3] Request Data: " << jstr << std::endl;

    auto functionReturn = executor(jstr);
    std::cout << "[Main3] Returned Value: " << functionReturn << std::endl;
}

void libTest4()
{
    // test 3: product
    auto jstr = generator("test3", Product{123, "My New Product"});
    std::cout << "[Main4] Request Data: " << jstr << std::endl;

    auto functionReturn = executor(jstr);
    std::cout << "[Main4] Returned Value: " << functionReturn << std::endl;
}

// MAIN

int main()
{
    mapping.push_back(MappingItem::create<bool, std::string>("test1", &test1, {"p1", "p2"}));
    mapping.push_back(MappingItem::create<std::string, float_t>("test2", &test2, {"p1", "p2"}));
    mapping.push_back(MappingItem::create<Product>("test3", &test3, {"prod"}));

    libTest1();
    libTest2();
    libTest3();
    libTest4();
}
