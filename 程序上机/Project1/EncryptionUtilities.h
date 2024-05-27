// EncryptionUtilities.h

#pragma once

#include <string>
using namespace std;
class EncryptionUtilities {
public:
    // 简单的数字对称加密函数，仅适用于纯数字字符串
    static string encryptDecrypt(const  string& input, int key);
};