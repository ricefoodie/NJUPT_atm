// FileHandler.h

#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "Account.h"
#include "VigenereCipher.h"

class FileHandler {
private:
    // 设置一个固定的密钥
    std::string key = "VigenereKey"; 

public:
    // 将账户信息写入文件
    static void writeAccountToFile(const Account& account) {
        VigenereCipher cipher;

        std::ofstream file("accounts.dat", std::ios::app); // 追加模式
        if (file.is_open()) {
            file << account.getID() << " ";
            file << account.getName() << " ";
            // 使用VigenereCipher加密密码并写入文件
            file << cipher.encrypt(account.getPassword(), "VigenereKey") << " ";
            file << account.getBalance() << "\n";
            file.close();
        }
        else {
            std::cerr << "无法打开文件写入账户信息。\n";
        }
    }

    // 从文件中读取账户信息并验证密码
    static bool verifyAccountLogin(const std::string& id, const std::string& password) {
        VigenereCipher cipher;

        std::ifstream file("accounts.dat");
        if (file.is_open()) {
            std::string fileID, fileName, fileEncryptedPassword;
            double fileBalance;

            while (file >> fileID >> fileName >> fileEncryptedPassword >> fileBalance) {
                // 如果找到匹配的ID，尝试解密并验证密码
                if (fileID == id) {
                    // 使用VigenereCipher的解密函数解密文件中的密码
                    std::string decryptedPassword = cipher.decrypt(fileEncryptedPassword,"VigenereKey");
                    std::cout << decryptedPassword << std::endl ;
                    // 比较解密后的密码与用户输入密码是否相同
                    return decryptedPassword == password;
                }
            }
            file.close();
            std::cerr << "账户ID未找到。\n";
        }
        else {
            std::cerr << "无法打开文件进行验证。\n";
        }
        return false;
    }
};