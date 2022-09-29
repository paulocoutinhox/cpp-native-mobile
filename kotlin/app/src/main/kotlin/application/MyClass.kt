package application

import java.util.ArrayList

class MyClass {
    constructor() {}

    fun test() {}

    fun testProduct(products: ArrayList<Product>): ArrayList<Product> {
        return ArrayList<Product>()
    }

    companion object {

        @JvmStatic fun staticTest() {}
    }
}
