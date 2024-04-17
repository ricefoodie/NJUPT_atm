#include "EncryptionUtilities.h"

    // 简单的数字对称加密函数，仅适用于纯数字字符串
    string EncryptionUtilities::encryptDecrypt(const  string& input, int key) {
        string result = input;

        for (char& c : result) {
            if (isdigit(c)) { // 仅处理数字字符
                // '0' - '9' 的ASCII值是 48 - 57
                // 将字符转换为0 - 9，进行加密操作，再转换回字符
                c = (c - '0' + key + 10) % 10 + '0';
            }
        }

        return result;
    }
