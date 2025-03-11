# UML类图
```
                          +------------------------+
                          |    AbstractFactory     |
                          +------------------------+
                          | + createProductA()     |
                          | + createProductB()     |
                          +------------------------+
                                    /   \
                                   /     \
                  +----------------+       +----------------+
                  | ConcreteFactory1|       | ConcreteFactory2|
                  +----------------+       +----------------+
                  | + createProductA()     | + createProductA()|
                  | + createProductB()     | + createProductB()|
                  +----------------+       +----------------+
                          |                          |
            +-------------+-------------+   +--------+---------+
            |                           |   |                  |
  +----------------------+   +----------------------+  +----------------------+   +----------------------+
  | ConcreteProductA1    |   | ConcreteProductB1    |  | ConcreteProductA2    |   | ConcreteProductB2    |
  +----------------------+   +----------------------+  +----------------------+   +----------------------+
  | + operationA()       |   | + operationB()       |  | + operationA()       |   | + operationB()       |
  +----------------------+   +----------------------+  +----------------------+   +----------------------+

```
- AbstractFactory：抽象工厂类，声明创建两类产品的接口。
- ConcreteFactory1/ConcreteFactory2：具体工厂，实现创建各自具体产品的接口。
- AbstractProductA / AbstractProductB：抽象产品类，分别定义产品 A 和产品 B 的接口。
- ConcreteProductA1, ConcreteProductA2：具体产品 A 的两个不同实现。
- ConcreteProductB1, ConcreteProductB2：具体产品 B 的两个不同实现。

# 编译方式
```
g++ -std=c++17 -Wall -o abstract_factory abstract_factory.cpp
```
