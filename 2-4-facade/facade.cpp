
#include <iostream>

//---------------------------
// 子系统组件（可替换为实际组件）
//---------------------------

class SubsystemA {
public:
    void operation1() { 
        std::cout << "SubsystemA: 执行操作1\n"; 
    }
    
    void operation2() { 
        std::cout << "SubsystemA: 执行操作2\n"; 
    }
};

class SubsystemB {
public:
    void initialize() { 
        std::cout << "SubsystemB: 初始化系统\n"; 
    }
    
    void processData() { 
        std::cout << "SubsystemB: 处理数据\n"; 
    }
};

class SubsystemC {
public:
    void validate() { 
        std::cout << "SubsystemC: 验证输入\n"; 
    }
    
    void cleanup() { 
        std::cout << "SubsystemC: 清理资源\n"; 
    }
};

//---------------------------
// 外观类（核心接口）
//---------------------------
class SystemFacade {
private:
    SubsystemA subsystemA;
    SubsystemB subsystemB;
    SubsystemC subsystemC;

public:
    // 统一入口方法
    void executeWorkflow() {
        std::cout << "\n=== 系统工作流开始 ===\n";
        
        subsystemC.validate();
        subsystemB.initialize();
        subsystemA.operation1();
        subsystemB.processData();
        subsystemA.operation2();
        subsystemC.cleanup();
        
        std::cout << "=== 系统工作流完成 ===\n\n";
    }

    // 可选：简化版接口
    void quickExecute() {
        std::cout << "\n[快速模式]\n";
        subsystemB.initialize();
        subsystemA.operation1();
        subsystemB.processData();
    }
};

//---------------------------
// 客户端代码
//---------------------------
int main() {
    SystemFacade facade;
    
    // 通过外观执行完整流程
    facade.executeWorkflow();
    
    // 执行简化流程
    facade.quickExecute();
    
    return 0;
}