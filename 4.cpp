#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Product {
private:
    int productId;
    string name;
    double price;
    int quantity;

public:
    Product(int productId, const string& name, double price, int quantity)
        : productId(productId), name(name), price(price), quantity(quantity) {}
    
    int getProductId() const { return productId; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    
    void setPrice(double price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    
    void display() const {
        cout << "Product ID: " << productId << ", Name: " << name 
                  << ", Price: $" << price << ", Quantity: " << quantity << endl;
    }
};

class Inventory {
private:
    vector<Product> products;
    
public:
    void addProduct(int productId, const string& name, double price, int quantity) {
        products.emplace_back(productId, name, price, quantity);
        cout << "Product added to inventory!\n";
    }
    
    void displayAllProducts() const {
        if (products.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }
        for (const auto& product : products) {
            product.display();
        }
    }
    
    Product* findProduct(int productId) {
        auto it = find_if(products.begin(), products.end(),
            [productId](const Product& p) { return p.getProductId() == productId; });
        return (it != products.end()) ? &(*it) : nullptr;
    }
    
    bool updateProduct(int productId, double price, int quantity) {
        Product* product = findProduct(productId);
        if (product) {
            product->setPrice(price);
            product->setQuantity(quantity);
            cout << "Product updated successfully!\n";
            return true;
        }
        cout << "Product not found!\n";
        return false;
    }
    
    bool removeProduct(int productId) {
        auto it = find_if(products.begin(), products.end(),
            [productId](const Product& p) { return p.getProductId() == productId; });
        if (it != products.end()) {
            products.erase(it);
            cout << "Product removed from inventory!\n";
            return true;
        }
        cout << "Product not found!\n";
        return false;
    }
};

int main() {
    Inventory inv;
    inv.addProduct(1, "Laptop", 999.99, 10);
    inv.addProduct(2, "Mouse", 25.50, 50);
    inv.displayAllProducts();
    inv.updateProduct(1, 899.99, 8);
    inv.removeProduct(2);
    inv.displayAllProducts();
    return 0;
}