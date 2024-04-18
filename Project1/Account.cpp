//Account.cpp
#include "Account.h"
//#include <iostream>
Account::Account(const string & id, const string & Name, const string & pw, double bal,int st)
{
    ID = id;          // 卡号
    name=Name;        // 用户姓名
    password=pw;    // 用户密码（已加密）
    balance=bal;          // 账户余额
    state = st;      //账户状态，0表示锁卡，1表示初始状态，2、3、4、5...表示登录次数
}
Account::~Account() {}
// 获取卡号
string Account::  getID() const { return ID; }
// 获取用户姓名
string Account:: getName() const { return name; }
// 获取密码
string Account::getPassword() const { return password; }
// 获取账户余额
double Account::getBalance() const { return balance; }
// 获取账户状态
int Account::getState() const { return state; }

//生成key
//int Account::generateKey(const  string& ID) {
//    int key;
//    key=stoi(ID)%10;
//	return key;
//}
// 设置卡号
void Account::setID(const  string& newID) { ID = newID; }
// 设置用户姓名
void Account::setName(const  string& newName) { name = newName; }
// 设置密码
void Account::setPassword(const  string& newPw) { password = newPw; }
// 设置账户余额
void Account::setBalance(double newBal) { balance = newBal; }
//设置状态
void Account::setState(int newSt) { state = newSt; }

// 存款函数
bool Account::deposit(double amount) {
    if (amount > 0) {
        updateBalance(balance + amount); // 调用 private 成员，更新余额
        cout << "存款成功！当前余额：" << balance << endl;
        return true;
    }
    else {
        cout << "请输入有效的金额。\n";
        return false;
    }
}

// 取款函数
bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        updateBalance(balance - amount); // 调用 private 成员，更新余额
        cout << "取款成功！当前余额：" << balance << endl;
        return true;
    }
    else {
        cout << (amount <= 0 ? "请输入有效的金额。\n" : "余额不足，取款失败。\n");
        return false;
    }
}

void Account::updateBalance(double newBalance) {
        balance = newBalance;
    }

int generateKey(const string& id) {
    int num = 0; // 初始化结果变量
    for (char c : id) { // 遍历字符串中的每个字符
        if (c >= '0' && c <= '9') { // 确保字符是数字
            num = num * 10 + (c - '0'); // 更新结果变量，'0' 到 '9' 的字符与 0 到 9 的整数映射
        }

    }
    return 5; // 返回结果
}