#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <any>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// product class
class Product
{
public:
    Product(int32_t id, std::string name, float size, bool inStock)
    {
        this->id = id;
        this->name = name;
        this->size = size;
        this->inStock = inStock;
    }

    std::string getName()
    {
        return this->name;
    }

private:
    int32_t id;
    std::string name;
    float size;
    bool inStock;
};

// test class
class MyClass
{
public:
    MyClass()
    {
        std::cout << "MyClass: Constructor" << std::endl;
    }

    static void test(const std::any &param)
    {
        std::cout << "MyClass: Test" << std::endl;

        /*
        auto prod = std::any_cast<Product>(param);
        std::cout << "Received Product Name: " << prod.getName() << std::endl;
        std::cout << "Received Product Address: " << &prod << std::endl;
        */

        auto value = std::any_cast<bool>(param);
        std::cout << "Received Value: " << value << std::endl;
    }

    static std::vector<Product> testProduct(Product product)
    {
        std::cout << "MyClass: Test Product" << std::endl;
        return {product, product};
    }

    static void testBool(bool value)
    {
        std::cout << "MyClass: Static Test" << std::endl;
    }
};

// main
int main()
{
    // list of mapping
    std::map<std::string, std::function<void(const std::any &)>> flist;
    flist["test"] = & MyClass::test;

    // general
    auto prod = Product{1, "Finny Candy", 123456.99123456, true};
    std::cout << "Product Address: " << &prod << std::endl;

    // method: test
    {
        // the json come from mobile (kotlin or swift)
        json j = json::parse(R"({
            "function": "test",
            "param": true
        })");

        auto function = j["function"].get<std::string>();
        //auto param = j["param"].get<std::any>(); // error here
        //flist[function](param);

        //main.cpp:94:33: error: no matching member function for call to 'get'
        //auto param = j["param"].get<std::any>();
        //            ~~~~~~~~~~~^~~~~~~~~~~~~
    }
}
