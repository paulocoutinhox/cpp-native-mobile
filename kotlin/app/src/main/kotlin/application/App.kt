package application

fun main() {
    println("Initializing...")

    // general
    val className = "application.MyClass"
    var methodName = ""

    val clz: Class<*> = Class.forName(className)

    println("OK")
}
