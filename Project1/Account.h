// Account.h

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
// 用户账户信息类
class Account {
private:
    std::string ID;          // 卡号
    std::string name;        // 用户姓名
    std::string password;    // 用户密码（已加密）
    double balance;          // 账户余额

public:
    // 构造函数
    Account(const std::string& id, const std::string& name, const std::string& pw, double bal)
        : ID(id), name(name), password(pw), balance(bal) {}

    // 获取卡号
    std::string getID() const { return ID; }
    // 获取用户姓名
    std::string getName() const { return name; }
    // 获取密码
    std::string getPassword() const { return password; }
    // 获取账户余额
    double getBalance() const { return balance; }

    // 设置卡号
    void setID(const std::string& newID) { ID = newID; }
    // 设置用户姓名
    void setName(const std::string& newName) { name = newName; }
    // 设置密码
    void setPassword(const std::string& newPw) { password = newPw; }
    // 设置账户余额
    void setBalance(double newBal) { balance = newBal; }

    // 存款函数
    bool deposit(double amount) {
        if (amount > 0) {
            updateBalance(balance + amount); // 调用 private 成员，更新余额
            std::cout << "存款成功！当前余额：" << balance << std::endl;
            return true;
        }
        else {
            std::cout << "请输入有效的金额。\n";
            return false;
        }
    }

    // 取款函数
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            updateBalance(balance - amount); // 调用 private 成员，更新余额
            std::cout << "取款成功！当前余额：" << balance << std::endl;
            return true;
        }
        else {
            std::cout << (amount <= 0 ? "请输入有效的金额。\n" : "余额不足，取款失败。\n");
            return false;
        }
    }
private:
    void updateBalance(double newBalance) {
        balance = newBalance;
    }
};