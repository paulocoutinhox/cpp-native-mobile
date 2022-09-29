package application

class Product {
    var id: Int
    var name: String
    var size: Float
    var inStock: Boolean

    constructor(id: Int, name: String, size: Float, inStock: Boolean) {
        this.id = id
        this.name = name
        this.size = size
        this.inStock = inStock
    }
}
