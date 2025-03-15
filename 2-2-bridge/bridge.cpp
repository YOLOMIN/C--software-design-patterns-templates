#include <iostream>
#include <memory>
using namespace std;

// 实现层接口
class Implementor {
public:
    virtual ~Implementor() = default;
    virtual void operationImpl() const = 0;
};

// 具体实现A
class ConcreteImplementorA : public Implementor {
public:
    void operationImpl() const override {
        cout << "ConcreteImplementorA operationImpl" << endl;
    }
};

// 具体实现B
class ConcreteImplementorB : public Implementor {
public:
    void operationImpl() const override {
        cout << "ConcreteImplementorB operationImpl" << endl;
    }
};

// 抽象层
class Abstraction {
protected:
    // 使用智能指针管理实现层对象
    unique_ptr<Implementor> implementor;
public:
    Abstraction(unique_ptr<Implementor> impl) : implementor(std::move(impl)) {}
    virtual ~Abstraction() = default;
    
    // 抽象操作，委托给实现层
    virtual void operation() const {
        implementor->operationImpl();
    }
};

// 扩展抽象层
class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(unique_ptr<Implementor> impl)
        : Abstraction(std::move(impl)) {}
    
    // 可扩展额外功能，然后调用基本操作
    void operation() const override {
        cout << "RefinedAbstraction: ";
        Abstraction::operation();
    }
};

int main() {
    // 使用 ConcreteImplementorA 构造 RefinedAbstraction
    unique_ptr<Abstraction> absA = make_unique<RefinedAbstraction>(make_unique<ConcreteImplementorA>());
    absA->operation();  // 输出：RefinedAbstraction: ConcreteImplementorA operationImpl
    
    // 切换为 ConcreteImplementorB
    unique_ptr<Abstraction> absB = make_unique<RefinedAbstraction>(make_unique<ConcreteImplementorB>());
    absB->operation();  // 输出：RefinedAbstraction: ConcreteImplementorB operationImpl

    return 0;
}
