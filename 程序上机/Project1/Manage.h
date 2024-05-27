//Manage.h
#pragma once
#include <windows.h>
#include "Account.h"
#include "Statement.h"
#include <fstream>
#include <iostream>
#include "FileHandler.h"
#include <limits>
#include <string>
#include <cctype>
#include <chrono>   
#include <ctime>    
#include <sstream>  
#include <iomanip>
#include <conio.h>
using namespace std;
class Manage
{
public:
	Manage();
	~Manage();
	// 获取当前时间函数实现
    string getCurrentTime();

// 创建账户的函数
    void createAccount();

// 创建定期存款账户的函数
    void createTimeDepositAccount();

// 验证登录的函数
    bool verifyLogin(string id);

// 使用独立的存取款函数
    void deposit(Account& account, double amount, int key);

    void withdraw(Account& account, double amount, int key);
// 查询余额
    void queryBalance(const  string& accountId, int key);
    void changePassword(const string& id, const int& key);
//查询交易历史记录
    void queryTransactionHistory(const  string& accountId, const int& key);
    double predictBal(const string& id, int key, double bal);


bool transfer(const  string& fromAccountId, const  string& toAccountId, double amount);



};

