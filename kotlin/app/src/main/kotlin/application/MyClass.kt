package application

import java.util.ArrayList

class MyClass {
    constructor() {
        println("MyClass: Constructor")
    }

    fun test() {
        println("MyClass: Test")
    }

    fun testProduct(products: ArrayList<Product>): ArrayList<Product> {
        return ArrayList<Product>()
    }

    companion object {
        @JvmStatic
        fun staticTest() {
            println("MyClass: Static Test")
        }
    }
}
