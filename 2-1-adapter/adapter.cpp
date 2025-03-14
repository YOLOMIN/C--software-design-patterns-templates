#include <iostream>

// 目标接口：客户端期望的接口
class Target {
public:
    virtual ~Target() = default;
    virtual void request() const = 0;
};

// 被适配者：已有功能但接口不兼容的类
class Adaptee {
public:
    void specificRequest() const {
        std::cout << "被适配者的方法被调用: specificRequest()" << std::endl;
    }
};

// 适配器类：通过组合方式实现对象适配器
class Adapter : public Target {
private:
    Adaptee* adaptee;  // 持有被适配者的引用（也可直接使用对象成员）

public:
    // 通过构造函数注入被适配对象
    Adapter(Adaptee* a) : adaptee(a) {}

    // 实现目标接口的请求方法
    void request() const override {
        std::cout << "适配器转换请求: ";
        adaptee->specificRequest();  // 委托给被适配者的方法
    }
};

// 可选：通过继承方式实现类适配器（需多重继承）
/*
class ClassAdapter 
    : public Target, 
      private Adaptee {  // 私有继承实现细节
public:
    void request() const override {
        std::cout << "类适配器转换请求: ";
        specificRequest();
    }
};
*/

int main() {
    // 创建被适配对象
    Adaptee adaptee;

    // 创建适配器并包装被适配对象
    Target* adapter = new Adapter(&adaptee);

    // 客户端通过目标接口调用方法
    adapter->request();  // 输出：适配器转换请求: 被适配者的方法被调用...

    delete adapter;
    return 0;
}