// FileHandler.h

#pragma once

#include "Account.h"
#include "EncryptionUtilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Statement.h"
using namespace std;
class FileHandler {

public:
    
    // 写入账户信息至文件
    static bool writeAccountToFile(const Account& account, int key);

    // 从文件中读取账户信息并验证密码
    static bool verifyAccountPassword(const  string& id, const  string& password, int key);
    // 更新账户密码
    static bool updatePassword(const  string& id, const  string& oldPassword,
        const  string& newPassword, int key);
    // 写入交易记录至文件
    static bool writeStatementToFile(const Statement& statement, const int& key);

    // 从文件中读取账户的所有交易流水记录
    static void readStatements(const  string& accountID, const int& key);

    // 更新账户余额
    static bool updateAccountBalance(const  string& id, double newBalance, int key);

    // 获取账户余额
    static double getAccountBalance(const  string& id, int key);
    
    // 按ID检索账户信息
    static Account* retrieveAccountById(const  string& id, int key);
    double getRandomizedSumByAccountId(const string& encryptedAccountID, int key);
};


