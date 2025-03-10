#include <iostream>
using namespace std;

class Singleton {
public:
    // 返回单例实例的引用，局部静态变量保证线程安全（C++11 起支持）
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
    
    // 删除复制构造函数和赋值运算符，防止复制
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    // 示例成员函数
    void doSomething() const {
        cout << "Singleton instance is doing something." << endl;
    }
    
private:
    // 私有构造函数，防止外部创建实例
    Singleton() {
        cout << "Singleton instance created." << endl;
    }
    
    // 可选：私有析构函数（根据需要）
    ~Singleton() = default;
};

int main() {
    // 获取单例实例并调用成员函数
    Singleton& instance = Singleton::getInstance();
    instance.doSomething();
    
    // 多次获取实例验证单例特性
    Singleton& instance2 = Singleton::getInstance();
    if (&instance == &instance2)
        cout << "Both instances are the same." << endl;
    
    return 0;
}
