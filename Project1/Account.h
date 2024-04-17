// Account.h

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
// 用户账户信息类
class Account {
public:
    string ID;          // 卡号
    string name;        // 用户姓名
    string password;    // 用户密码（已加密）
    double balance;          // 账户余额

public:
    // 构造函数
    Account(const  string& id, const  string& Name, const  string& pw, double bal);
    ~Account();//析构函数

    // 获取卡号
    string getID() const;
    // 获取用户姓名
    string getName() const;
    // 获取密码
    string getPassword() const;
    // 获取账户余额
    double getBalance() const;
    //生成key
   // static int generateKey(const  string& ID);
    // 设置卡号
    void setID(const  string& newID);
    // 设置用户姓名
    void setName(const  string& newName);
    // 设置密码
    void setPassword(const  string& newPw);
    // 设置账户余额
    void setBalance(double newBal);

    // 存款函数
    bool deposit(double amount);

    // 取款函数
    bool withdraw(double amount);
private:
    void updateBalance(double newBalance);

};
int generateKey(const  string& id);