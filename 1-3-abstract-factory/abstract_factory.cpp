#include <iostream>
#include <memory>
using namespace std;

// 抽象产品 A
class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;
    virtual void operationA() const = 0;
};

// 抽象产品 B
class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;
    virtual void operationB() const = 0;
};

// 具体产品 A1（ConcreteProductA1）
class ConcreteProductA1 : public AbstractProductA {
public:
    void operationA() const override {
        cout << "Operation A in ConcreteProductA1" << endl;
    }
};

// 具体产品 B1（ConcreteProductB1）
class ConcreteProductB1 : public AbstractProductB {
public:
    void operationB() const override {
        cout << "Operation B in ConcreteProductB1" << endl;
    }
};

// 具体产品 A2（ConcreteProductA2）
class ConcreteProductA2 : public AbstractProductA {
public:
    void operationA() const override {
        cout << "Operation A in ConcreteProductA2" << endl;
    }
};

// 具体产品 B2（ConcreteProductB2）
class ConcreteProductB2 : public AbstractProductB {
public:
    void operationB() const override {
        cout << "Operation B in ConcreteProductB2" << endl;
    }
};

// 抽象工厂类
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual unique_ptr<AbstractProductB> createProductB() const = 0;
};

// 具体工厂 1：生产 ConcreteProductA1 和 ConcreteProductB1
class ConcreteFactory1 : public AbstractFactory {
public:
    unique_ptr<AbstractProductA> createProductA() const override {
        return make_unique<ConcreteProductA1>();
    }
    unique_ptr<AbstractProductB> createProductB() const override {
        return make_unique<ConcreteProductB1>();
    }
};

// 具体工厂 2：生产 ConcreteProductA2 和 ConcreteProductB2
class ConcreteFactory2 : public AbstractFactory {
public:
    unique_ptr<AbstractProductA> createProductA() const override {
        return make_unique<ConcreteProductA2>();
    }
    unique_ptr<AbstractProductB> createProductB() const override {
        return make_unique<ConcreteProductB2>();
    }
};

int main() {
    // 使用具体工厂1创建产品族1
    unique_ptr<AbstractFactory> factory = make_unique<ConcreteFactory1>();
    auto productA = factory->createProductA();
    auto productB = factory->createProductB();
    productA->operationA();
    productB->operationB();
    
    // 切换到具体工厂2，创建产品族2
    factory = make_unique<ConcreteFactory2>();
    productA = factory->createProductA();
    productB = factory->createProductB();
    productA->operationA();
    productB->operationB();
    
    return 0;
}
