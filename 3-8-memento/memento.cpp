#include <iostream>
#include <memory>
#include <string>
using namespace std;

// 备忘录：封装了 Originator 对象的内部状态
class Memento {
private:
    string state;
public:
    explicit Memento(const string &s) : state(s) {}
    string getState() const { return state; }
};

// 发起人：创建备忘录并可以从备忘录恢复状态
class Originator {
private:
    string state;
public:
    void setState(const string &s) {
        state = s;
        cout << "Originator: State set to \"" << state << "\"" << endl;
    }
    
    string getState() const { return state; }
    
    // 保存当前状态到备忘录
    unique_ptr<Memento> saveStateToMemento() {
        cout << "Originator: Saving state to Memento." << endl;
        return make_unique<Memento>(state);
    }
    
    // 从备忘录恢复状态
    void getStateFromMemento(const Memento &memento) {
        state = memento.getState();
        cout << "Originator: State restored from Memento: \"" << state << "\"" << endl;
    }
};

// 看护者：负责保存备忘录，但不操作其内容
class Caretaker {
private:
    unique_ptr<Memento> memento;
public:
    void setMemento(unique_ptr<Memento> m) {
        memento = move(m);
    }
    const Memento* getMemento() const { return memento.get(); }
};

int main() {
    Originator originator;
    Caretaker caretaker;
    
    // 设置初始状态
    originator.setState("State #1");
    originator.setState("State #2");
    
    // 保存当前状态
    caretaker.setMemento(originator.saveStateToMemento());
    
    // 修改状态
    originator.setState("State #3");
    
    // 恢复状态
    if (caretaker.getMemento()) {
        originator.getStateFromMemento(*caretaker.getMemento());
    }
    
    return 0;
}
