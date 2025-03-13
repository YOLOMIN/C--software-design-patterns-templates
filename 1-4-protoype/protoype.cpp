#include <iostream>
#include <memory>
#include <unordered_map>

// 抽象原型基类
class Prototype {
public:
    virtual ~Prototype() = default;
    
    // 克隆接口（返回智能指针避免内存泄漏）
    virtual std::unique_ptr<Prototype> clone() const = 0;
    
    // 示例方法（可根据实际需求扩展）
    virtual void printInfo() const = 0;
};

// 具体原型类
class ConcretePrototype : public Prototype {
private:
    int _value;        // 基础类型成员
    std::string _name; // 字符串成员（自动深拷贝）

public:
    // 构造函数
    ConcretePrototype(int value, std::string name)
        : _value(value), _name(std::move(name)) {}
    
    // 拷贝构造函数（显式定义深拷贝逻辑）
    ConcretePrototype(const ConcretePrototype& other)
        : _value(other._value), _name(other._name) {}
    
    // 克隆实现：通过拷贝构造函数创建新对象
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype>(*this);
    }
    
    // 修改数据方法（测试深拷贝效果）
    void setValue(int value) { _value = value; }
    void setName(const std::string& name) { _name = name; }
    
    // 信息输出
    void printInfo() const override {
        std::cout << "ConcretePrototype [Value: " << _value 
                  << ", Name: " << _name << "]" << std::endl;
    }
};

// 原型管理器（可选扩展）
class PrototypeManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Prototype>> _prototypes;

public:
    // 注册原型
    void registerPrototype(const std::string& key, std::unique_ptr<Prototype> proto) {
        _prototypes[key] = std::move(proto);
    }
    
    // 获取克隆副本
    std::unique_ptr<Prototype> create(const std::string& key) {
        if (_prototypes.find(key) != _prototypes.end()) {
            return _prototypes[key]->clone();
        }
        return nullptr;
    }
};

// 使用示例
int main() {
    // 1. 基础克隆示例
    ConcretePrototype original(42, "Original");
    auto clone = original.clone();
    
    std::cout << "Original: ";
    original.printInfo();       // 输出: ConcretePrototype [Value: 42, Name: Original]
    std::cout << "Clone:    ";
    clone->printInfo();         // 输出: ConcretePrototype [Value: 42, Name: Original]
    
    // 修改原对象，验证克隆对象独立性
    original.setValue(100);
    original.setName("Modified");
    std::cout << "\nAfter modifying original:" << std::endl;
    std::cout << "Original: ";
    original.printInfo();       // 输出: Value: 100, Name: Modified
    std::cout << "Clone:    ";
    clone->printInfo();         // 输出: Value: 42, Name: Original（未受影响）
    
    // 2. 使用原型管理器
    PrototypeManager manager;
    manager.registerPrototype("default", std::make_unique<ConcretePrototype>(0, "Default"));
    
    auto defaultClone = manager.create("default");
    if (defaultClone) {
        std::cout << "\nManaged clone: ";
        defaultClone->printInfo(); // 输出: Value: 0, Name: Default
    }
    
    return 0;
}