#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <functional>

// defines
typedef void (*FuncPtrType)();

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

    static void test()
    {
        std::cout << "MyClass: Test" << std::endl;
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
    std::map<std::string, FuncPtrType> funs;

    funs["test"] = & MyClass::test;
    // funs["testProduct"] = & MyClass::testProduct;
    // funs["testBool"] = & MyClass::testBool;

    // method static test
    funs["test"]();
}
