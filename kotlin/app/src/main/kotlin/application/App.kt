package application

// functions
fun showProducts(list: ArrayList<Product>) {
    for (i in list) {
        println(i.name)
    }
}

// main
@Suppress("UNCHECKED_CAST")
fun main() {
    println("Initializing...")

    // general
    val className = "application.MyClass"
    lateinit var methodName: String

    // create obj from string
    val cls: Class<*> = Class.forName(className)
    val ctr = cls.getConstructor()
    val obj = ctr.newInstance()
    val kotlinClass = cls.kotlin

    // method static test
    methodName = "staticTest"
    cls.getMethod(methodName)?.let { method -> method.invoke(kotlinClass) }

    // method test
    methodName = "test"
    cls.getMethod(methodName)?.let { method -> method.invoke(obj) }

    // method test product
    methodName = "testProduct"
    lateinit var result1: Any
    val prod = Product(99, "Finny Candy", 123456.99123456f, true)

    cls.getMethod(methodName, prod.javaClass)?.let { method ->
        result1 = method.invoke(obj, prod)
        println(result1)
    }

    // use return value and send back
    lateinit var result2: Any

    (result1 as? ArrayList<Product>)?.let { result ->
        cls.getMethod(methodName, result[0].javaClass)?.let { method ->
            result2 = method.invoke(obj, result[0])
            println(result2)
        }
    }

    (result2 as? ArrayList<Product>)?.let { result -> showProducts(result) }

    // finish
    println("OK")
}
