// main.cpp
#include <windows.h>
#include "Account.h"
#include "EncryptionUtilities.h"
#include <fstream>
#include <iostream>

int main() {
    // 用户的原始信息
    std::string userID = "1234567890";
    std::string userName = "1234";
    std::string userPassword = "password123";
    double userBalance = 1000.50;

    // 加密用户信息
    userID = EncryptionUtilities::caesarEncrypt(userID, 3);
    userName = EncryptionUtilities::caesarEncrypt(userName, 3);  // 请注意这只适用于ASCII字符
    userPassword = EncryptionUtilities::caesarEncrypt(userPassword, 3);

    // 将加密信息写入文件
    std::ofstream outfile("accounts.dat", std::ios::binary | std::ios::app);
    if (!outfile) {
        std::cerr << "无法打开文件进行写入。\n";
        return -1;
    }

    outfile.write(userID.c_str(), userID.size());
    outfile.write(userName.c_str(), userName.size());
    outfile.write(userPassword.c_str(), userPassword.size());
    outfile.write(reinterpret_cast<const char*>(&userBalance), sizeof(userBalance));

    outfile.close();

    std::cout << "用户信息写入成功。\n";


    return 0;
}