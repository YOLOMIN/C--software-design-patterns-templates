#include <iostream>
#include <memory>
using namespace std;

// 抽象主题：定义了真实主题和代理共同实现的接口
class Subject {
public:
    virtual ~Subject() = default;
    virtual void request() const = 0;
};

// 真实主题：实现了抽象主题的具体业务逻辑
class RealSubject : public Subject {
public:
    void request() const override {
        cout << "RealSubject: Handling request." << endl;
    }
};

// 代理类：实现了与真实主题相同的接口，并控制对真实主题的访问
class Proxy : public Subject {
private:
    // 代理内部可以延迟创建真实主题，也可以直接传入真实主题对象
    mutable unique_ptr<RealSubject> realSubject;
    
    // 模拟检查权限或其他预处理工作
    bool checkAccess() const {
        cout << "Proxy: Checking access prior to firing a real request." << endl;
        // 在实际应用中，可根据具体条件返回 true/false
        return true;
    }
    
    // 模拟日志记录等后置操作
    void logAccess() const {
        cout << "Proxy: Logging the time of request." << endl;
    }
    
public:
    void request() const override {
        // 预处理：权限检查等
        if (checkAccess()) {
            // 延迟创建真实主题
            if (!realSubject) {
                // 当第一次请求时，创建真实主题对象
                realSubject = make_unique<RealSubject>();
            }
            // 委托真实主题处理请求
            realSubject->request();
            // 后处理：日志记录等
            logAccess();
        } else {
            cout << "Proxy: Access denied." << endl;
        }
    }
};

int main() {
    // 客户端只与抽象主题交互，实际的操作由代理处理
    unique_ptr<Subject> proxy = make_unique<Proxy>();
    proxy->request();
    
    return 0;
}
