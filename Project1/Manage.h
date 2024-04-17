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

/*
void transfer(Account& fromAccount, Account& toAccount, double amount, int key) {
    // ... (之前的扣款和存款逻辑)

    // 转账成功后记录交易流水
    if (fromAccountBalanceUpdated && toAccountBalanceUpdated) {
        // 获取系统当前时间作为交易流水编号
         string transactionId = getCurrentTime(); // 假设 getCurrentTime 已经实现

        // 创建转出方的交易流水记录对象
        Statement outStatement(
            transactionId, // 唯一的交易编号
            fromAccount.getID(),
            getCurrentTime(), // 当前时间
            TransactionType::TRANSFER, // 交易类型
            -amount, // 转账金额（负值代表支出）
            toAccount.getID() // 收款方账户ID
        );

        // 将交易流水记录写入文件
        FileHandler::writeStatementToFile(outStatement);

         cout << "转账交易已记录。\n";
    }
}
*/

bool transfer(const  string& fromAccountId, const  string& toAccountId, double amount);



};

