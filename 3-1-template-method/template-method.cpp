#include <iostream>
using namespace std;

// 抽象类：定义模板方法和基本步骤
class AbstractClass {
public:
    virtual ~AbstractClass() = default;
    
    // 模板方法：定义算法的骨架，调用多个步骤
    void templateMethod() const {
        step1();
        step2();
        step3();
        step4(); // 钩子方法，子类可选择重写
    }
    
    // 具体步骤：固定部分，父类已实现
    void step1() const {
        cout << "AbstractClass: step1 (固定步骤)" << endl;
    }
    
    // 抽象步骤：子类必须实现
    virtual void step2() const = 0;
    
    // 具体步骤：固定部分，父类已实现
    void step3() const {
        cout << "AbstractClass: step3 (固定步骤)" << endl;
    }
    
    // 钩子方法：默认空实现，子类可选择性重写
    virtual void step4() const {}
};

// 具体子类：实现抽象步骤和钩子方法
class ConcreteClass : public AbstractClass {
public:
    void step2() const override {
        cout << "ConcreteClass: step2 (定制行为)" << endl;
    }
    
    void step4() const override {
        cout << "ConcreteClass: step4 (定制钩子行为)" << endl;
    }
};

int main() {
    ConcreteClass concrete;
    concrete.templateMethod();
    return 0;
}
