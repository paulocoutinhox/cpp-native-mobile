package application

import java.util.ArrayList

class MyClass {
    constructor() {
        println("MyClass: Constructor")
    }

    fun test() {
        println("MyClass: Test")
    }

    fun testProduct(product: Product): ArrayList<Product> {
        println("MyClass: Test Product")
        return arrayListOf(product, product)
    }

    companion object {
        @JvmStatic
        fun staticTest() {
            println("MyClass: Static Test")
        }
    }
}
