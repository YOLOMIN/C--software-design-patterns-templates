#include <iostream>

// 抽象处理者
class Handler {
protected:
    Handler* nextHandler;

public:
    Handler() : nextHandler(nullptr) {}
    virtual ~Handler() = default;

    void setNext(Handler* handler) {
        nextHandler = handler;
    }

    void handleRequest(int request) {
        if (canHandle(request)) {
            process(request);
        } else if (nextHandler != nullptr) {
            nextHandler->handleRequest(request);
        } else {
            std::cout << "No handler found for request: " << request << std::endl;
        }
    }

protected:
    virtual bool canHandle(int request) = 0;
    virtual void process(int request) = 0;
};

// 具体处理者A
class ConcreteHandlerA : public Handler {
protected:
    bool canHandle(int request) override {
        return request < 0;
    }

    void process(int request) override {
        std::cout << "ConcreteHandlerA processed negative request: " << request << std::endl;
    }
};

// 具体处理者B
class ConcreteHandlerB : public Handler {
protected:
    bool canHandle(int request) override {
        return request == 0;
    }

    void process(int request) override {
        std::cout << "ConcreteHandlerB processed zero request: " << request << std::endl;
    }
};

// 具体处理者C
class ConcreteHandlerC : public Handler {
protected:
    bool canHandle(int request) override {
        return request > 0;
    }

    void process(int request) override {
        std::cout << "ConcreteHandlerC processed positive request: " << request << std::endl;
    }
};

// 客户端代码
int main() {
    Handler* handlerA = new ConcreteHandlerA();
    Handler* handlerB = new ConcreteHandlerB();
    Handler* handlerC = new ConcreteHandlerC();

    handlerA->setNext(handlerB);
    handlerB->setNext(handlerC);

    // 测试不同请求
    handlerA->handleRequest(-5);  // A处理
    handlerA->handleRequest(0);   // B处理
    handlerA->handleRequest(42);  // C处理
    handlerA->handleRequest(100); // C处理

    delete handlerA;
    delete handlerB;
    delete handlerC;

    return 0;
}