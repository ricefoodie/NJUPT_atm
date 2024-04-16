// FileHandler.h

#pragma once

#include "Account.h"
#include "EncryptionUtilities.h"
#include <iostream>
#include <fstream>
#include <sstream>

class FileHandler {
public:
    // 写入账户信息至文件
    static bool writeAccountToFile(const Account& account, int key) {
        std::ofstream fileOut("accounts.dat", std::ios::app); // 使用追加模式
        if (!fileOut) {
            std::cerr << "无法打开文件写入。\n";
            return false;
        }
        fileOut << EncryptionUtilities::encryptDecrypt(account.getID(), key) << " "
            << account.getName() << " "
            << EncryptionUtilities::encryptDecrypt(account.getPassword(), key) << " "
            << account.getBalance() << std::endl;
        fileOut.close();
        return true;
    }

    // 从文件中读取账户信息并验证密码
    static bool verifyAccountPassword(const std::string& id, const std::string& password, int key) {
        std::ifstream fileIn("accounts.dat");
        if (!fileIn) {
            std::cerr << "无法打开文件读取。\n";
            return false;
        }

        std::string line;
        while (std::getline(fileIn, line)) {
            std::istringstream iss(line);
            std::string fileID, filePassword, fileName;
            double fileBalance;
            if (iss >> fileID >> fileName>> filePassword >> fileBalance) {
                if (fileID == EncryptionUtilities::encryptDecrypt(id, -key) &&
                    EncryptionUtilities::encryptDecrypt(filePassword, -key) == password) {
                    fileIn.close();
                    return true;
                }
            }
        }
        fileIn.close();
        return false;
    }
    // 更新账户密码
    static bool updatePassword(const std::string& id, const std::string& oldPassword, const std::string& newPassword, int key) {
        // 使用一个临时文件存储新的账户信息
        std::string tempFilename = "accounts_temp.dat";
        std::ifstream file("accounts.dat");
        std::ofstream tempFile(tempFilename);

        bool isUpdated = false;
        if (file.is_open() && tempFile.is_open()) {
            std::string fileID, fileName, filePassword;
            double fileBalance;

            while (file >> fileID >> fileName >> filePassword >> fileBalance) {
                if (fileID == EncryptionUtilities::encryptDecrypt(id, -key)) {
                    // 解密并比较密码
                    std::string decryptedPassword = EncryptionUtilities::encryptDecrypt(filePassword, -key);
                    if (decryptedPassword == oldPassword) {
                        // 若旧密码正确，使用新密码并加密后写入临时文件
                        isUpdated = true;
                        filePassword = EncryptionUtilities::encryptDecrypt(newPassword, key);
                    }
                    else {
                        // 旧密码不正确，不更新信息，返回失败
                        std::cerr << "旧密码不正确，无法更新。\n";
                        return false;
                    }
                }
                // 将账户信息写入临时文件中
                tempFile << fileID << " " << fileName << " " << filePassword << " " << fileBalance << "\n";
            }

            file.close();
            tempFile.close();

            if (isUpdated) {
                // 使用新的账户文件替换旧的文件
                remove("accounts.dat");
                rename(tempFilename.c_str(), "accounts.dat");
            }
            else {
                // 若没有更新任何内容，删除临时文件
                remove(tempFilename.c_str());
                std::cerr << "没有找到对应的账户进行更新。\n";
            }

        }
        else {
            std::cerr << "无法打开文件进行更新。\n";
            return false;
        }
        return isUpdated;
    }
    // 写入交易记录至文件
    static bool writeStatementToFile(const Statement& statement) {
        std::ofstream fileOut("statements.dat", std::ios::app); // 使用追加模式打开交易流水记录文件
        if (!fileOut) {
            std::cerr << "无法打开文件写入交易记录。\n";
            return false;
        }

        // 存入交易信息，格式化为流水编号 账户卡号 交易时间 交易类型 交易金额 对方账户
        fileOut << statement.getID() << " "
            << statement.getAccountID() << " "
            << statement.getTime() << " "
            << statement.getType() << " "
            << statement.getAmount() << " "
            << statement.getToAccountID() << std::endl;
        fileOut.close();
        return true;
    }

    // 从文件中读取账户的所有交易流水记录
    static void readStatements(const std::string& accountID) {
        std::ifstream fileIn("statements.dat");
        if (!fileIn) {
            std::cerr << "无法打开文件读取交易记录。\n";
            return;
        }

        std::string line;
        std::cout << "流水编号 账户卡号 交易时间 交易类型 交易金额 对方账户\n";
        while (getline(fileIn, line)) {
            
            std::istringstream iss(line);
            std::string id, accID, time, toAccID;
            int type;
            double amount;
            if (iss >> id >> accID >> time >> type >> amount >> toAccID) {
                //std::cout << 1 << std::endl;
                if (accID == accountID) {
                    std::cout << id << " " << accID << " " << time << " " << type << " " << amount << " " << toAccID << std::endl;
                }
                else {
                    //std::cout << accID << std::endl;
                }
            }
        }
        fileIn.close();
    }

    // 更新账户余额
    static bool updateAccountBalance(const std::string& id, double newBalance, int key) {
        std::ifstream fileIn("accounts.dat");
        std::ofstream fileOut("accounts_temp.dat");
        bool isUpdated = false;

        if (fileIn && fileOut) {
            std::string fileID, fileName, filePassword;
            double fileBalance;
            while (fileIn >> fileID >> fileName >> filePassword >> fileBalance) {
                if (fileID == EncryptionUtilities::encryptDecrypt(id, -key)) {
                    fileBalance = newBalance;  // 更新余额
                    isUpdated = true;
                }
                fileOut << fileID
                    << " " << fileName << " "
                    << filePassword << " "
                    << fileBalance << std::endl;
            }
            fileIn.close();
            fileOut.close();

            // 删除旧账户文件并将临时文件重命名为新账户文件
            remove("accounts.dat");
            rename("accounts_temp.dat", "accounts.dat");
        }
        else {
            std::cerr << "无法打开文件进行更新。\n";
            if (fileIn) fileIn.close();
            if (fileOut) {
                fileOut.close();
                remove("accounts_temp.dat");  // 删除临时文件
            }
            return false;
        }
        return isUpdated;
    }

    // 获取账户余额
    static double getAccountBalance(const std::string& id, int key) {
        std::ifstream fileIn("accounts.dat");
        if (!fileIn) {
            std::cerr << "无法打开文件来获取余额。\n";
            return -1; // 使用错误值表示无法获取余额
        }

        std::string fileID, fileName, filePassword;
        double fileBalance;
        while (fileIn >> fileID >> fileName >> filePassword >> fileBalance) {
            if (fileID == EncryptionUtilities::encryptDecrypt(id, -key)) {
                fileIn.close();
                return fileBalance; // 返回解密后的账户余额
            }
        }
        fileIn.close();
        std::cerr << "没找到对应的账户余额。\n";
        return -1; // 使用错误值表示账户不存在
    }
    
    // 按ID检索账户信息
    static Account* retrieveAccountById(const std::string& id, int key) {
        std::ifstream fileIn("accounts.dat");
        if (!fileIn) {
            std::cerr << "无法打开文件读取账户信息。\n";
            return nullptr; // 返回 nullptr 表示没找到账户
        }

        std::string fileID, fileName, filePassword;
        double fileBalance;
        while (fileIn >> fileID >> fileName >> filePassword >> fileBalance) {
            // 解密并检查ID是否匹配
            if (EncryptionUtilities::encryptDecrypt(fileID, -key) == id) {
                fileIn.close();
                // 返回动态分配的对应的账户对象
                return new Account(id, fileName, filePassword, fileBalance);
            }
        }

        fileIn.close();
        std::cerr << "未找到匹配的账户ID。\n";
        return nullptr; // 未找到账户，返回 nullptr
    }
    /*
    //转账
    void transfer(Account& fromAccount, Account& toAccount, double amount, int key) {
        // 确认支付方的余额是否足够
        double fromBalance = FileHandler::getAccountBalance(fromAccount.getID(), key);
        if (fromBalance < amount) {
            std::cout << "付款方余额不足，转账失败。\n";
            return;
        }

        // 在账户文件中减少付款方的余额并增加收款方的余额
        if (fromAccount.withdraw(amount)) {
            FileHandler::updateAccountBalance(fromAccount.getID(), fromAccount.getBalance(), key);
            if (toAccount.deposit(amount)) {
                FileHandler::updateAccountBalance(toAccount.getID(), toAccount.getBalance(), key);
                std::cout << "转账成功！\n";
            }
            else {
                // 如果收款失败，需要回滚付款方的扣款
                fromAccount.deposit(amount);
                FileHandler::updateAccountBalance(fromAccount.getID(), fromAccount.getBalance(), key);
                std::cout << "转账失败，收款方账户问题。\n";
            }
        }
        else {
            std::cout << "转账失败，扣款未成功。\n";
        }

        // 记录交易到流水记录文件
        // ... 记录付款方的支出
        // ... 记录收款方的收入
    }
    */
};


