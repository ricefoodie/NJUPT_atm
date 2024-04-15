// main.cpp
#include <windows.h>
#include "Account.h"
#include <fstream>
#include <iostream>
#include "FileHandler.h"
#include <limits>
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
// 验证登录的函数
void verifyLogin() {
    std::string id, password;

    std::cout << "请输入卡号: ";
    std::cin >> id;
    std::cout << "请输入密码: ";
    std::cin >> password;

    if (FileHandler::verifyAccountPassword(id, password, 5)) {
        std::cout << "密码验证成功，欢迎登陆！\n";
    }
    else {
        std::cout << "密码验证失败，卡号或密码错误。\n";
    }
}


int main() {
    while (1)
    {
        std::cout << "ATM系统\n";
        std::cout << "0. 退出\n";
        std::cout << "1. 创建账户\n";
        std::cout << "2. 验证密码\n";
        std::cout << "3. 修改密码\n";
        std::cout << "请选择一个选项: ";

        int option;
        std::cin >> option;

        switch (option) {
        case 1:
            createAccount();
            break;
        case 2:
            verifyLogin();
            break;
        case 3: {
            std::string id = "123";
            int key = 5;
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
        }
        case 0:
            return 0;
        default:
            std::cout << "无效选项，请重新选择。\n";
            break;
        }
    }
    
}