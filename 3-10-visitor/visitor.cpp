#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// 前向声明具体元素类
class ConcreteElementA;
class ConcreteElementB;

// 访问者接口：定义访问各个具体元素的方法
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visitConcreteElementA(const ConcreteElementA &element) = 0;
    virtual void visitConcreteElementB(const ConcreteElementB &element) = 0;
};

// 元素接口：定义接受访问者的方法
class Element {
public:
    virtual ~Element() = default;
    virtual void accept(Visitor &visitor) const = 0;
};

// 具体元素 A
class ConcreteElementA : public Element {
public:
    void accept(Visitor &visitor) const override {
        visitor.visitConcreteElementA(*this);
    }
    void operationA() const {
        cout << "ConcreteElementA: operationA executed." << endl;
    }
};

// 具体元素 B
class ConcreteElementB : public Element {
public:
    void accept(Visitor &visitor) const override {
        visitor.visitConcreteElementB(*this);
    }
    void operationB() const {
        cout << "ConcreteElementB: operationB executed." << endl;
    }
};

// 具体访问者：实现访问各个具体元素的操作
class ConcreteVisitor : public Visitor {
public:
    void visitConcreteElementA(const ConcreteElementA &element) override {
        cout << "ConcreteVisitor: Processing ConcreteElementA." << endl;
        element.operationA();
    }
    void visitConcreteElementB(const ConcreteElementB &element) override {
        cout << "ConcreteVisitor: Processing ConcreteElementB." << endl;
        element.operationB();
    }
};

int main() {
    // 创建一个元素集合
    vector<shared_ptr<Element>> elements;
    elements.push_back(make_shared<ConcreteElementA>());
    elements.push_back(make_shared<ConcreteElementB>());
    
    // 创建访问者
    ConcreteVisitor visitor;
    
    // 遍历所有元素，让访问者访问每个元素
    for (const auto &elem : elements) {
        elem->accept(visitor);
    }
    
    return 0;
}
