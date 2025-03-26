#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 前向声明
class Colleague;

// 抽象中介者
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void sendMessage(const std::string& message, std::shared_ptr<Colleague> colleague) = 0;
};

// 抽象同事类
class Colleague : public std::enable_shared_from_this<Colleague> {
protected:
    std::shared_ptr<Mediator> mediator;
public:
    explicit Colleague(std::shared_ptr<Mediator> m) : mediator(std::move(m)) {}
    virtual ~Colleague() = default;
    virtual void send(const std::string& message) {
        mediator->sendMessage(message, shared_from_this());
    }
    virtual void receive(const std::string& message) = 0;
};

// 具体同事类A
class ConcreteColleagueA : public Colleague {
public:
    using Colleague::Colleague;
    void receive(const std::string& message) override {
        std::cout << "Colleague A received: " << message << std::endl;
    }
};

// 具体同事类B
class ConcreteColleagueB : public Colleague {
public:
    using Colleague::Colleague;
    void receive(const std::string& message) override {
        std::cout << "Colleague B received: " << message << std::endl;
    }
};

// 具体中介者
class ConcreteMediator : public Mediator {
private:
    std::vector<std::shared_ptr<Colleague>> colleagues;
public:
    void addColleague(std::shared_ptr<Colleague> colleague) {
        colleagues.push_back(colleague);
    }
    void sendMessage(const std::string& message, std::shared_ptr<Colleague> sender) override {
        for (const auto& colleague : colleagues) {
            if (colleague != sender) {
                colleague->receive(message);
            }
        }
    }
};

int main() {
    auto mediator = std::make_shared<ConcreteMediator>();

    auto colleagueA = std::make_shared<ConcreteColleagueA>(mediator);
    auto colleagueB = std::make_shared<ConcreteColleagueB>(mediator);

    mediator->addColleague(colleagueA);
    mediator->addColleague(colleagueB);

    colleagueA->send("Hello from A");
    colleagueB->send("Hello from B");

    return 0;
}
