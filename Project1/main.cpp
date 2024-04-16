// main.cpp
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

// 获取当前时间函数实现
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now(); // 获取当前时间点
    auto nowTimeT = std::chrono::system_clock::to_time_t(now); // 转换为time_t
    std::tm localTime;

    // 使用localtime_s代替localtime
    localtime_s(&localTime, &nowTimeT);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y%m%d%H%M%S"); // 格式化输出
    return oss.str();
}

// 创建账户的函数
void createAccount() {
    std::string id, name, password;
    double balance;

    std::cout << "请输入卡号: ";
    std::cin >> id;
    std::cout << "请输入姓名: ";
    std::cin >> name;
    std::cout << "请输入密码: ";
    std::cin >> password;
    std::cout << "请输入账户初始余额: ";
    std::cin >> balance;

    // 创建账户实例
    Account newAccount(id, name, password, balance);

    // 写入文件
    if (FileHandler::writeAccountToFile(newAccount, 5)) {
        std::cout << "账户创建成功！\n";
    }
    else {
        std::cout << "账户创建失败，请稍后再试。\n";
    }
}


// 验证登录的函数
bool verifyLogin(std::string id) {
    std::string  password;
    std::cout << "请输入密码: ";
    std::cin >> password;

    if (FileHandler::verifyAccountPassword(id, password, 5)) {
        std::cout << "密码验证成功，欢迎登陆！\n";
        return true;
    }
    else {
        std::cout << "密码验证失败，卡号或密码错误。\n";
        return false;
    }
}

// 使用独立的存取款函数
void deposit(Account& account, double amount, int key) {
    double currentBalance = FileHandler::getAccountBalance(account.getID(), key);
    // 检查余额是否有效且存款额为正
    if (currentBalance >= 0 && amount > 0) {
        account.deposit(amount);
        FileHandler::updateAccountBalance(account.getID(), account.getBalance(), key);
        // 更新账户余额后再次创建并写入 Statement
        Statement depositStatement(getCurrentTime(), account.getID(),
            getCurrentTime(), TransactionType::DEPOSIT, amount, "self");
        FileHandler::writeStatementToFile(depositStatement);
    }
    else {
        std::cout << "存款失败。" << std::endl;
    }
}

void withdraw(Account& account, double amount, int key) {
    double currentBalance = FileHandler::getAccountBalance(account.getID(), key);
    // 检查取款金额是否合法
    if (currentBalance >= amount && amount > 0) {
        account.withdraw(amount);
        FileHandler::updateAccountBalance(account.getID(), account.getBalance(), key);
        // 更新账户余额后再次创建并写入 Statement
        Statement withdrawStatement(getCurrentTime(), account.getID(),
            getCurrentTime(), TransactionType::WITHDRAWAL, amount, "self");
        FileHandler::writeStatementToFile(withdrawStatement);
    }
    else {
        std::cout << (amount <= 0 ? "请输入有效的金额。\n" : "余额不足，取款失败。\n");
    }
}
// 查询余额
void queryBalance(const std::string& accountId, int key) {
    // 调用 FileHandler 函数获取账户余额
    double balance = FileHandler::getAccountBalance(accountId, key);
    if (balance >= 0) {
        std::cout << "当前余额是：" << balance << std::endl;
    }
    else {
        std::cout << "查询余额失败。" << std::endl;
    }
}

//查询交易历史记录
void queryTransactionHistory(const std::string& accountId) {
    std::cout << "查询交易历史记录中...\n";
    // 调用 FileHandler 的方法来读取并打印交易记录
    FileHandler::readStatements(accountId);
}

/*
void transfer(Account& fromAccount, Account& toAccount, double amount, int key) {
    // ... (之前的扣款和存款逻辑)

    // 转账成功后记录交易流水
    if (fromAccountBalanceUpdated && toAccountBalanceUpdated) {
        // 获取系统当前时间作为交易流水编号
        std::string transactionId = getCurrentTime(); // 假设 getCurrentTime 已经实现

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

        std::cout << "转账交易已记录。\n";
    }
}
*/

bool transfer(const std::string& fromAccountId, const std::string& toAccountId, double amount, int key) {
    // 检索付款方账户
    Account* fromAccount = FileHandler::retrieveAccountById(fromAccountId, key);
    if (fromAccount == nullptr) {
        std::cerr << "付款方账户不存在。\n";
        return false;
    }

    // 检索收款方账户
    Account* toAccount = FileHandler::retrieveAccountById(toAccountId, key);
    if (toAccount == nullptr) {
        std::cerr << "收款方账户不存在。\n";
        delete fromAccount; // 释放已分配的付款方资源
        return false;
    }

    // 执行转账
    if (fromAccount->withdraw(amount)) {
        if (toAccount->deposit(amount)) {
            // 更新两个账户的余额
            FileHandler::updateAccountBalance(fromAccount->getID(), fromAccount->getBalance(), key);
            FileHandler::updateAccountBalance(toAccount->getID(), toAccount->getBalance(), key);

            // 创建交易记录并写入文件
            Statement fromStatement(getCurrentTime(), fromAccountId, getCurrentTime(), TransactionType::TRANSFER, -amount, toAccountId);
            FileHandler::writeStatementToFile(fromStatement);
            /*
            Statement toStatement(getCurrentTime(), toAccountId, getCurrentTime(), TransactionType::TRANSFER, amount, fromAccountId);
            FileHandler::writeStatementToFile(toStatement);
            */
            delete fromAccount; // 释放资源
            delete toAccount;
            std::cerr << "转账成功！\n";
            return true;
        }
        else {
            // 若收款方存款失败，回滚付款方的取款
            fromAccount->deposit(amount);
        }
    }

    // 清理资源
    delete fromAccount;
    delete toAccount;
    return false;
}


int main()
{
    
    std::cout << "ATM系统\n";
    std::cout << "0. 退出\n";
    std::cout << "1. 管理员\n";
    std::cout << "2. 用户\n";
    std::cout << "请选择一个选项: ";
    int option;
    std::cin >> option;
    switch (option) {
    case 1:
        createAccount();
        break;
    case 2:
    {
        int loginAttempts = 0;//登录错误计数器
        std::string id;
        int key = 5;
        Account* currentAccount;
        do {
            std::cout << "请输入正确的卡号: ";
            std::cin >> id;

            currentAccount = FileHandler::retrieveAccountById(id, key);
        } while (currentAccount == nullptr);
       

            // 记得操作完成后删除 Account 对象以释放内存
            //delete currentAccount;
        
        while (!verifyLogin(id)) {//先登录
            loginAttempts++;

            if (loginAttempts < 3) {
                std::cout << "密码输入错误，你已经输错了 " << loginAttempts << " 次，还剩" << 3 - loginAttempts << "次机会！" << std::endl;
            }
            else {
                std::cout << "锁卡！" << std::endl;
                // 这里可以添加锁定账户或卡的逻辑
                return 1; // 退出程序或按需要处理。
            }
        }
        //到这里已经成功登录    
        std::cout << "ATM系统\n";
        std::cout << "0. 返回\n";
        std::cout << "1. 存款\n";
        std::cout << "2. 取款\n";
        std::cout << "3. 转账\n";
        std::cout << "4. 余额查询\n";
        std::cout << "5. 历史交易查询\n";
        std::cout << "6. 修改密码\n";
        std::cout << "请选择一个选项: ";
        int option2;
        std::cin >> option2;
        switch (option2) {
        case 1: {   // 存款
            double depositAmount;
            std::cout << "请输入存款金额:";
            std::cin >> depositAmount;
            deposit(*currentAccount, depositAmount,key);  // 使用存款函数
            break;
        }
        case 2: {   // 取款
            double withdrawAmount;
            std::cout << "请输入取款金额:";
            std::cin >> withdrawAmount;
            withdraw(*currentAccount, withdrawAmount ,key);  // 使用取款函数
            break;
        }
        case 3: {
            std::string  toAccountId;
            double amount;
            std::cout << "请输入收款方账号: ";
            std::cin >> toAccountId;
            std::cout << "请输入转账金额: ";
            std::cin >> amount;

            // 执行转账
            bool success = transfer(id, toAccountId, amount, key);
            if (success) {
                std::cout << "转账成功。\n";
            }
            else {
                std::cout << "转账失败。\n";
            }
        }
        case 4: {//余额查询
            queryBalance(id, key);
            break;
        }
        case 5: {//查询交易历史记录
            queryTransactionHistory(id);
            break;
        }
        case 6: {//修改密码
            std::string oldPassword, newPassword;
            std::cout << "oldpassword:";
            std::cin >> oldPassword;
            std::cout << "newpassword:";
            std::cin >> newPassword;
            bool passwordChanged = FileHandler::updatePassword(id, oldPassword, newPassword, key);
            if (passwordChanged) {
                std::cout << "密码更新成功！" << std::endl;
            }
            else {
                std::cout << "密码更新失败。" << std::endl;
            }
            break;
        }
        case 0:
            break;
        }
    }
    case 0:
        break;
    }
    return 0;
}


/*
int main() {
    
    std::string id1="0001", id2 = "123", time="123456", toAccountID="123456789",name="123",password="123",id3="1234";
    double amount = 1, balance = 1000;
    int type = 1,key=5;
    Statement newStatement(id1,id2,time,type,amount, toAccountID);
    Account newAccount(id2, name, password, balance);
    withdraw(newAccount,amount,key);
    std::cout <<FileHandler::getAccountBalance(id2,key);
    FileHandler::readStatements(id2);
    transfer(id2, id3, 400, key);
}*/

