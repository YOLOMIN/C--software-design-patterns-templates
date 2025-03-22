#include <iostream>
#include <memory>
using namespace std;

// 策略接口：定义算法接口
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void algorithmInterface() const = 0;
};

// 具体策略 A：实现策略接口，提供具体算法实现
class ConcreteStrategyA : public Strategy {
public:
    void algorithmInterface() const override {
        cout << "ConcreteStrategyA: Executing algorithm A." << endl;
    }
};

// 具体策略 B：实现策略接口，提供另一种算法实现
class ConcreteStrategyB : public Strategy {
public:
    void algorithmInterface() const override {
        cout << "ConcreteStrategyB: Executing algorithm B." << endl;
    }
};

// 上下文（Context）：持有一个策略对象，并通过策略对象执行算法
class Context {
private:
    // 使用智能指针管理策略对象
    unique_ptr<Strategy> strategy;
public:
    // 设置策略
    void setStrategy(unique_ptr<Strategy> strat) {
        strategy = std::move(strat);
    }
    
    // 执行算法：委托给当前策略
    void executeStrategy() const {
        if(strategy) {
            strategy->algorithmInterface();
        } else {
            cout << "No strategy set." << endl;
        }
    }
};

int main() {
    Context context;
    
    // 使用 ConcreteStrategyA 执行算法
    context.setStrategy(make_unique<ConcreteStrategyA>());
    context.executeStrategy();
    
    // 切换为 ConcreteStrategyB 执行另一种算法
    context.setStrategy(make_unique<ConcreteStrategyB>());
    context.executeStrategy();
    
    return 0;
}
