import Foundation

// initialize
print("Initializing...")

// extensions
extension NSObject {
    class func fromClassName(className : String) -> NSObject.Type {
        #if os(iOS) || os(watchOS) || os(tvOS)
            let className = Bundle.main.infoDictionary!["CFBundleName"] as! String + "." + className
            return NSClassFromString(className) as! NSObject.Type
        #else
            let className = "main" + "." + className
            return NSClassFromString(className) as! NSObject.Type
        #endif
    }
}

// classes
class Product: NSObject, Codable {
    let id: Int
    let name: String
    let size: Float
    let inStock: Bool

    init(id: Int, name: String, size: Float, inStock: Bool) {
        self.id = id
        self.name = name
        self.size = size
        self.inStock = inStock
    }

    deinit {
        print("Product: Destructor")
        showMemoryAddr(obj: self, prefix: "Product:")
    }
}

class MyClass : NSObject
{
    override init() {
        print("MyClass: Constructor")
    }

    deinit {
        print("MyClass: Destructor")
    }

    @objc
    public func test() {
        print("MyClass: Test")
    }

    @objc
    public static func staticTest() {
        print("MyClass: Static Test")
    }

    @objc
    public func testProduct(_ product: Product) -> [Product] {
        return [product, product]
    }
}

// functions
func showProducts(list: [Product]) {
    for i in list {
        print(i.name)
    }
}

func showMemoryAddr(obj : AnyObject, prefix: String) {
    print("\(prefix): ", Unmanaged.passUnretained(obj).toOpaque())
}

// general
let className = "MyClass"
var methodName = ""

// create obj from string
let c = NSObject.fromClassName(className: className)
let obj = c.init()

// method static test
methodName = "staticTest";
guard c.responds(to: NSSelectorFromString(methodName)) else {
    print("Error: Static method '\(methodName)' don't exists on '\(className)'")
    exit(0)
}

c.perform(NSSelectorFromString(methodName))

// method test
methodName = "test";
guard obj.responds(to: NSSelectorFromString(methodName)) else {
    print("Error: Method '\(methodName)' don't exists on '\(className)'")
    exit(0)
}

obj.perform(NSSelectorFromString(methodName))

// method test product
let prod = Product(id: 99, name: "Finny Candy", size: 123456.99123456, inStock: true)
showMemoryAddr(obj: prod, prefix: "Product")

let result1 = obj.perform(NSSelectorFromString("testProduct:"), with: prod)
print(result1!)

// use return value (umanaged) and send back to cxx
let result2 = result1?.takeUnretainedValue()

if let result2 = result2 as? [Product] {
    let result3 = obj.perform(NSSelectorFromString("testProduct:"), with: result2[0]).takeUnretainedValue()
    print(result3)

    if let result3 = result3 as? [Product] {
        // show products
        showProducts(list: result3)
    }
}

// finish
print("OK")
