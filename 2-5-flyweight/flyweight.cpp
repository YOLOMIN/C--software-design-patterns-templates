#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
using namespace std;

// 享元接口：定义操作方法
class Flyweight {
public:
    virtual ~Flyweight() = default;
    // 操作方法，extrinsicState 为外蕴状态
    virtual void operation(const string &extrinsicState) const = 0;
};

// 具体享元类：存储内部状态（intrinsic state），可以共享
class ConcreteFlyweight : public Flyweight {
private:
    string intrinsicState;  // 内蕴状态，不随外部环境变化
public:
    ConcreteFlyweight(const string &state) : intrinsicState(state) {}
    void operation(const string &extrinsicState) const override {
        cout << "ConcreteFlyweight: [intrinsic: " << intrinsicState 
             << ", extrinsic: " << extrinsicState << "]" << endl;
    }
};

// 享元工厂：负责创建和管理享元对象，确保共享
class FlyweightFactory {
private:
    unordered_map<string, shared_ptr<Flyweight>> flyweights;
public:
    // 获取享元对象，如果已存在则返回共享对象，否则创建新对象
    shared_ptr<Flyweight> getFlyweight(const string &key) {
        auto it = flyweights.find(key);
        if (it != flyweights.end()) {
            return it->second;
        } else {
            auto flyweight = make_shared<ConcreteFlyweight>(key);
            flyweights.insert({key, flyweight});
            return flyweight;
        }
    }
    
    // 列出当前享元对象的数量
    void listFlyweights() const {
        cout << "FlyweightFactory: Total " << flyweights.size() << " flyweights:" << endl;
        for (const auto &pair : flyweights) {
            cout << "  " << pair.first << endl;
        }
    }
};

int main() {
    FlyweightFactory factory;
    
    // 请求享元对象，"A" 和 "B" 为内蕴状态标识
    auto fly1 = factory.getFlyweight("A");
    auto fly2 = factory.getFlyweight("B");
    auto fly3 = factory.getFlyweight("A");  // 与 fly1 应该共享同一个对象

    // 调用操作方法，传入外部状态
    fly1->operation("Extrinsic 1");
    fly2->operation("Extrinsic 2");
    fly3->operation("Extrinsic 3");

    // 输出享元对象池中的对象数量
    factory.listFlyweights();

    return 0;
}
