// Statement.h

#pragma once
#include <iostream>
#include <string>
using namespace std;
// 交易流水记录类
class Statement {
private:
     string ID;            // 流水编号
     string accountID;     // 对应账户的卡号
     string time;          // 交易时间
     int type;                  // 交易类型，可以用枚举定义具体类型
     double amount;             // 交易金额
     string toAccountID;   // 对方账户的卡号（转账时使用）

public:
    // 构造函数
    Statement(const  string& id, const  string& accID, const  string& tm, int ty, double amt, const  string& toAccID);
    ~Statement();//析构函数
    // 获取流水编号
    string getID() const;
    // 获取账户卡号
     string getAccountID() const;
    // 获取交易时间
     string getTime() const;
     int getType() const;
    // 获取交易金额
    double getAmount() const;
    // 获取对方账户卡号
    string getToAccountID() const;

    // 设置流水编号
     void setID(const  string& newID);
    // 设置账户卡号
    void setAccountID(const  string& newAccountID);
    // 设置交易时间
    void setTime(const  string& newTime);
    // 设置交易类型
    void setType(int newType);
    // 设置交易金额
    void setAmount(double newAmount);
    // 设置对方账户卡号
    void setToAccountID(const  string& newToAccountID);

    // 此处可以添加其他成员函数...
};

// 交易类型枚举
enum TransactionType {
    DEPOSIT = 1,   // 存款
    WITHDRAWAL,    // 取款
    TRANSFER       // 转账
};