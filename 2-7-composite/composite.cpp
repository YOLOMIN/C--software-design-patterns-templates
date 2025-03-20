#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
using namespace std;

// 抽象组件：定义统一的接口
class Component {
public:
    virtual ~Component() = default;
    // 统一操作，客户端通过调用 operation() 来执行任务
    virtual void operation() const = 0;
    
    // 默认实现为空，叶子组件不支持添加或移除子组件
    virtual void add(shared_ptr<Component> component) {}
    virtual void remove(shared_ptr<Component> component) {}
};

// 叶子组件：不包含子组件
class Leaf : public Component {
private:
    string name;
public:
    Leaf(const string& n) : name(n) {}
    void operation() const override {
        cout << "Leaf [" << name << "] operation." << endl;
    }
};

// 组合组件：可以包含子组件（既可以是叶子也可以是其他组合）
class Composite : public Component {
private:
    string name;
    vector<shared_ptr<Component>> children;
public:
    Composite(const string& n) : name(n) {}
    
    void operation() const override {
        cout << "Composite [" << name << "] operation." << endl;
        for (const auto &child : children) {
            child->operation();
        }
    }
    
    // 添加子组件
    void add(shared_ptr<Component> component) override {
        children.push_back(component);
    }
    
    // 移除子组件
    void remove(shared_ptr<Component> component) override {
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
    }
};

int main() {
    // 创建叶子节点
    shared_ptr<Component> leaf1 = make_shared<Leaf>("Leaf1");
    shared_ptr<Component> leaf2 = make_shared<Leaf>("Leaf2");
    shared_ptr<Component> leaf3 = make_shared<Leaf>("Leaf3");

    // 创建组合节点
    shared_ptr<Component> composite1 = make_shared<Composite>("Composite1");
    composite1->add(leaf1);
    composite1->add(leaf2);

    // 创建顶级组合节点
    shared_ptr<Component> composite2 = make_shared<Composite>("Composite2");
    composite2->add(composite1);
    composite2->add(leaf3);

    // 客户端调用顶级组合对象的操作
    composite2->operation();

    return 0;
}
