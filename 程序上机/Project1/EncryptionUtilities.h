// EncryptionUtilities.h

#pragma once

#include <string>
using namespace std;
class EncryptionUtilities {
public:
    // �򵥵����ֶԳƼ��ܺ������������ڴ������ַ���
    static string encryptDecrypt(const  string& input, int key);
};