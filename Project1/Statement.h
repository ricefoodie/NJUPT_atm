// Statement.h

#pragma once

#include <string>

// 交易流水记录类
class Statement {
private:
    std::string ID;            // 流水编号
    std::string accountID;     // 对应账户的卡号
    std::string time;          // 交易时间
    int type;                  // 交易类型，可以用枚举定义具体类型
    double amount;             // 交易金额
    std::string toAccountID;   // 对方账户的卡号（转账时使用）

public:
    // 构造函数
    Statement(const std::string& id, const std::string& accID,
        const std::string& tm, int ty, double amt, const std::string& toAccID)
        : ID(id), accountID(accID), time(tm), type(ty), amount(amt), toAccountID(toAccID) {}

    // 获取流水编号
    std::string getID() const { return ID; }
    // 获取账户卡号
    std::string getAccountID() const { return accountID; }
    // 获取交易时间
    std::string getTime() const { return time; }
    // 获取交易类型
    int getType() const { return type; }
    // 获取交易金额
    double getAmount() const { return amount; }
    // 获取对方账户卡号
    std::string getToAccountID() const { return toAccountID; }

    // 设置流水编号
    void setID(const std::string& newID) { ID = newID; }
    // 设置账户卡号
    void setAccountID(const std::string& newAccountID) { accountID = newAccountID; }
    // 设置交易时间
    void setTime(const std::string& newTime) { time = newTime; }
    // 设置交易类型
    void setType(int newType) { type = newType; }
    // 设置交易金额
    void setAmount(double newAmount) { amount = newAmount; }
    // 设置对方账户卡号
    void setToAccountID(const std::string& newToAccountID) { toAccountID = newToAccountID; }

    // 此处可以添加其他成员函数...
};

// 交易类型枚举
enum TransactionType {
    DEPOSIT = 1,   // 存款
    WITHDRAWAL,    // 取款
    TRANSFER       // 转账
};