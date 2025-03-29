#include <iostream>
#include <memory>
#include <string>
using namespace std;

// 状态接口：定义状态相关的操作
class State {
public:
    virtual ~State() = default;
    // 定义状态行为接口，context 作为参数传递给状态对象
    virtual void handle(class Context* context) = 0;
};

// 前向声明 Context

// 具体状态类：ConcreteStateA
class ConcreteStateA : public State {
public:
    void handle(Context* context) override;
};

// 具体状态类：ConcreteStateB
class ConcreteStateB : public State {
public:
    void handle(Context* context) override;
};

// 环境类：Context，维护一个 State 对象
class Context {
private:
    unique_ptr<State> currentState;
public:
    Context(unique_ptr<State> state) : currentState(move(state)) {}
    
    // 设置当前状态
    void setState(unique_ptr<State> state) {
        currentState = move(state);
    }
    
    // 请求处理：委托给当前状态处理
    void request() {
        currentState->handle(this);
    }
    
    // 获取当前状态描述（仅供演示，可扩展）
    string getStateName() const;
};

// 在此处定义 Context::getStateName() 的实现，用于演示状态切换
string Context::getStateName() const {
    // 此处仅作示例，实际可通过类型识别或内部数据来返回状态名称
    // 为简单起见，这里不作复杂实现
    return "当前状态";
}

// 具体状态 A 的 handle 实现：切换到状态 B
void ConcreteStateA::handle(Context* context) {
    cout << "ConcreteStateA handling request, switching to ConcreteStateB." << endl;
    // 状态切换：创建状态 B 并设置给 context
    context->setState(make_unique<ConcreteStateB>());
}

// 具体状态 B 的 handle 实现：切换到状态 A
void ConcreteStateB::handle(Context* context) {
    cout << "ConcreteStateB handling request, switching to ConcreteStateA." << endl;
    // 状态切换：创建状态 A 并设置给 context
    context->setState(make_unique<ConcreteStateA>());
}

int main() {
    // 初始状态设置为 ConcreteStateA
    Context context(make_unique<ConcreteStateA>());
    
    // 模拟状态切换
    cout << "Initial state: ConcreteStateA" << endl;
    context.request();  // 从状态 A 切换到状态 B
    context.request();  // 从状态 B 切换到状态 A
    context.request();  // 再次切换
    
    return 0;
}
