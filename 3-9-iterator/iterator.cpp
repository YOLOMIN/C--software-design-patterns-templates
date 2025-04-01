#include <iostream>
#include <vector>

// 定义迭代器接口模板
template <typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    // 判断是否还有下一个元素
    virtual bool hasNext() = 0;
    // 返回下一个元素
    virtual T next() = 0;
};

// 定义聚合对象接口模板
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() {}
    // 创建一个用于遍历聚合对象的迭代器
    virtual Iterator<T>* createIterator() = 0;
};

// 具体迭代器，实现 Iterator 接口
template <typename T>
class ConcreteIterator : public Iterator<T> {
private:
    const std::vector<T>& items;
    size_t index;
public:
    ConcreteIterator(const std::vector<T>& items) : items(items), index(0) {}

    bool hasNext() override {
        return index < items.size();
    }

    T next() override {
        return items[index++];
    }
};

// 具体聚合对象，实现 Aggregate 接口
template <typename T>
class ConcreteAggregate : public Aggregate<T> {
private:
    std::vector<T> items;
public:
    // 添加元素
    void add(const T& item) {
        items.push_back(item);
    }

    Iterator<T>* createIterator() override {
        return new ConcreteIterator<T>(items);
    }
};

int main() {
    // 构造具体聚合对象并添加数据
    ConcreteAggregate<int> aggregate;
    aggregate.add(10);
    aggregate.add(20);
    aggregate.add(30);

    // 通过聚合对象获取迭代器
    Iterator<int>* it = aggregate.createIterator();
    while (it->hasNext()) {
        std::cout << it->next() << std::endl;
    }
    delete it; // 释放内存

    return 0;
}
