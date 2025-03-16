#include <iostream>
#include <memory>
using namespace std;

// 抽象组件：定义接口
class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;
};

// 具体组件：实现抽象组件接口
class ConcreteComponent : public Component {
public:
    void operation() const override {
        cout << "ConcreteComponent operation." << endl;
    }
};

// 抽象装饰器：同样实现 Component 接口，并持有一个 Component 对象
class Decorator : public Component {
protected:
    // 这里使用智能指针管理组件，确保内存安全
    unique_ptr<Component> component;
public:
    Decorator(unique_ptr<Component> comp) : component(std::move(comp)) {}
    
    // 默认实现调用被装饰对象的 operation()
    void operation() const override {
        if (component)
            component->operation();
    }
};

// 具体装饰器A：增加额外的行为
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(unique_ptr<Component> comp) : Decorator(std::move(comp)) {}
    
    void operation() const override {
        // 调用被装饰对象的 operation()
        Decorator::operation();
        // 添加新的职责
        cout << "ConcreteDecoratorA additional behavior." << endl;
    }
};

// 具体装饰器B：增加前置和后置行为
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(unique_ptr<Component> comp) : Decorator(std::move(comp)) {}
    
    void operation() const override {
        cout << "ConcreteDecoratorB pre-processing." << endl;
        // 调用被装饰对象的 operation()
        Decorator::operation();
        cout << "ConcreteDecoratorB post-processing." << endl;
    }
};

int main() {
    // 创建基础组件
    unique_ptr<Component> component = make_unique<ConcreteComponent>();
    
    // 使用 ConcreteDecoratorA 装饰基础组件
    component = make_unique<ConcreteDecoratorA>(std::move(component));
    
    // 再使用 ConcreteDecoratorB 装饰，叠加新的行为
    component = make_unique<ConcreteDecoratorB>(std::move(component));
    
    // 调用操作方法，输出所有装饰的效果
    component->operation();
    
    return 0;
}
