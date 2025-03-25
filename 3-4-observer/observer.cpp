#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// 观察者接口：定义一个更新接口，供主题通知观察者时调用
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const string &message) = 0;
};

// 主题接口：定义注册、注销和通知观察者的方法
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(shared_ptr<Observer> observer) = 0;
    virtual void detach(shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
};

// 具体主题：当状态发生变化时通知所有观察者
class ConcreteSubject : public Subject {
private:
    vector<shared_ptr<Observer>> observers;
    string state; // 状态，可以根据需要扩展为其他数据类型
public:
    void setState(const string &s) {
        state = s;
        notify(); // 状态更新后通知观察者
    }
    string getState() const {
        return state;
    }
    
    void attach(shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }
    
    void detach(shared_ptr<Observer> observer) override {
        // 使用 remove-erase idiom 进行移除
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    
    void notify() override {
        for (const auto &observer : observers) {
            observer->update(state);
        }
    }
};

// 具体观察者：实现 Observer 接口，根据主题状态进行响应更新
class ConcreteObserver : public Observer {
private:
    string name;
public:
    ConcreteObserver(const string &n) : name(n) {}
    void update(const string &message) override {
        cout << "Observer [" << name << "] received update: " << message << endl;
    }
};

int main() {
    // 创建主题对象
    auto subject = make_shared<ConcreteSubject>();
    
    // 创建观察者并注册到主题
    auto observer1 = make_shared<ConcreteObserver>("Observer1");
    auto observer2 = make_shared<ConcreteObserver>("Observer2");
    
    subject->attach(observer1);
    subject->attach(observer2);
    
    // 更新主题状态，观察者会收到通知
    subject->setState("State changed to 1");
    
    // 注销其中一个观察者，再次更新状态
    subject->detach(observer1);
    subject->setState("State changed to 2");
    
    return 0;
}
