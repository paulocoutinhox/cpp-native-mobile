package application

fun main() {
    println("Initializing...")

    // general
    val className = "application.MyClass"
    var methodName = ""

    // create obj from string
    val cls: Class<*> = Class.forName(className)
    val cons = cls.getConstructor()
    val obj = cons.newInstance()
    val kotlinClass = cls.kotlin

    // method static test
    methodName = "staticTest"
    cls.getMethod(methodName)?.let { method ->
        method.invoke(kotlinClass.objectInstance)
    }

    // method test
    methodName = "test"
    cls.getMethod(methodName)?.let { method ->
        method.invoke(obj)
    }

    // method test product
    val prod = Product(99, "Finny Candy", 123456.99123456f, true)

    cls.getMethod(methodName)?.let { method ->
        val result1 = method.invoke("testProduct", prod)
        println(result1)
    }

    println("OK")
}
