#include <iostream>
#include <memory>
#include <vector>

// Receiver
class Light {
public:
    void on() { std::cout << "Light is ON\n"; }
    void off() { std::cout << "Light is OFF\n"; }
};

// Command接口
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete Command
class LightOnCommand : public Command {
    Light* light;
public:
    explicit LightOnCommand(Light* l) : light(l) {}
    void execute() override { light->on(); }
    void undo() override { light->off(); }
};

class LightOffCommand : public Command {
    Light* light;
public:
    explicit LightOffCommand(Light* l) : light(l) {}
    void execute() override { light->off(); }
    void undo() override { light->on(); }
};

// Invoker
class RemoteControl {
    std::vector<std::unique_ptr<Command>> history;
    std::unique_ptr<Command> currentCommand; // ✨ 改用智能指针管理当前命令
public:
    void setCommand(std::unique_ptr<Command> cmd) {
        currentCommand = std::move(cmd);
    }
    
    void pressButton() {
        currentCommand->execute();
        history.push_back(std::move(currentCommand)); // ✨ 转移所有权到history
    }
    
    void undoLast() {
        if (!history.empty()) {
            history.back()->undo();
            history.pop_back(); // ✨ 直接移除，不需手动释放
        }
    }
};

// ==================== 使用示例 ====================
int main() {
    Light light;
    RemoteControl remote;
    
    LightOnCommand onCmd(&light);
    LightOffCommand offCmd(&light);

    // 测试开灯
    remote.setCommand(std::make_unique<LightOnCommand>(&light));
    remote.pressButton();  // Light is ON
    
    // 测试关灯
    remote.setCommand(std::make_unique<LightOffCommand>(&light));
    remote.pressButton();  // Light is OFF
    
    // 测试撤销
    remote.undoLast();     // Light is ON
    remote.undoLast();     // Light is OFF

    return 0;
}