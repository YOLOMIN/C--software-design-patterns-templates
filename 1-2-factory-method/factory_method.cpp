#include <iostream>
#include <memory>
using namespace std;

// 抽象产品类：定义产品接口
class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

// 具体产品A
class ConcreteProductA : public Product {
public:
    void use() const override {
        cout << "Using ConcreteProductA" << endl;
    }
};

// 具体产品B
class ConcreteProductB : public Product {
public:
    void use() const override {
        cout << "Using ConcreteProductB" << endl;
    }
};

// 抽象工厂（Creator）：声明创建产品的纯虚工厂方法
class Creator {
public:
    virtual ~Creator() = default;
    
    // 工厂方法，子类负责实现
    virtual unique_ptr<Product> createProduct() const = 0;
    
    // 示例操作：利用工厂方法创建产品并调用产品的业务操作
    void someOperation() const {
        // 通过工厂方法创建产品
        unique_ptr<Product> product = createProduct();
        // 使用产品
        product->use();
    }
};

// 具体工厂A：生产 ConcreteProductA
class ConcreteCreatorA : public Creator {
public:
    unique_ptr<Product> createProduct() const override {
        return make_unique<ConcreteProductA>();
    }
};

// 具体工厂B：生产 ConcreteProductB
class ConcreteCreatorB : public Creator {
public:
    unique_ptr<Product> createProduct() const override {
        return make_unique<ConcreteProductB>();
    }
};

int main() {
    // 通过具体工厂A创建并使用产品A
    unique_ptr<Creator> creatorA = make_unique<ConcreteCreatorA>();
    creatorA->someOperation();
    
    // 通过具体工厂B创建并使用产品B
    unique_ptr<Creator> creatorB = make_unique<ConcreteCreatorB>();
    creatorB->someOperation();
    
    return 0;
}
