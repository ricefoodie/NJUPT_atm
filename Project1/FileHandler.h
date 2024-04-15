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
        fileOut << EncryptionUtilities::encryptDecrypt(account.getID(), key)
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
                if (fileID == id &&
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
};


