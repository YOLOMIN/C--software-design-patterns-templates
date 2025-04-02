#include <iostream>
#include <memory>
using namespace std;

// 抽象表达式类：定义解释操作接口
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() const = 0;
};

// 终结符表达式：数字表达式
class NumberExpression : public Expression {
private:
    int number;
public:
    explicit NumberExpression(int n) : number(n) {}
    int interpret() const override {
        return number;
    }
};

// 非终结符表达式：加法表达式
class PlusExpression : public Expression {
private:
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    PlusExpression(unique_ptr<Expression> l, unique_ptr<Expression> r)
        : left(move(l)), right(move(r)) {}
    int interpret() const override {
        return left->interpret() + right->interpret();
    }
};

// 非终结符表达式：减法表达式
class MinusExpression : public Expression {
private:
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    MinusExpression(unique_ptr<Expression> l, unique_ptr<Expression> r)
        : left(move(l)), right(move(r)) {}
    int interpret() const override {
        return left->interpret() - right->interpret();
    }
};

int main() {
    // 构造表达式: (7 - 3) + 2
    unique_ptr<Expression> expr = make_unique<PlusExpression>(
        make_unique<MinusExpression>(
            make_unique<NumberExpression>(7),
            make_unique<NumberExpression>(3)
        ),
        make_unique<NumberExpression>(2)
    );

    cout << "Result: " << expr->interpret() << endl;  // 输出：Result: 6
    return 0;
}
