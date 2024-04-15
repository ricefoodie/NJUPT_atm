// main.cpp
#include <windows.h>
#include "Account.h"
#include <fstream>
#include <iostream>
#include "FileHandler.h"


#include <iostream>
#include <string>
#include <cctype>

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

    Account newAccount(id, name, password, balance);
    FileHandler::writeAccountToFile(newAccount);
    std::cout << "账户创建成功！\n";
}

// 验证登录的函数
void verifyLogin() {
    std::string id, password;

    std::cout << "请输入卡号: ";
    std::cin >> id;
    std::cout << "请输入密码: ";
    std::cin >> password;

    if (FileHandler::verifyAccountLogin(id, password)) {
        std::cout << "密码验证成功！\n";
    }
    else {
        std::cout << "密码验证失败！\n";
    }
}
/*
int main() {
    int choice;

    std::cout << "请选择操作：\n";
    std::cout << "1. 创建账户\n";
    std::cout << "2. 验证登录\n";
    std::cin >> choice;

    switch (choice) {
    case 1:
        createAccount();
        break;
    case 2:
        verifyLogin();
        break;
    default:
        std::cout << "无效选项。\n";
    }

    return 0;
}

*/
int main() {
    VigenereCipher cipher;

    // 示例明文和密钥
    std::string plaintext = "Hello123World";
    std::string key = "VIGENERECIPHERKEY";

    std::cout << "Original text : " << plaintext << "\n";
    std::cout << "Key           : " << key << "\n";

    // 加密
    std::string encryptedText = cipher.encrypt(plaintext, key);
    std::cout << "Encrypted text: " << encryptedText << "\n";

    // 解密
    std::string decryptedText = cipher.decrypt(encryptedText, key);
    std::cout << "Decrypted text: " << decryptedText << "\n";

    return 0;
}