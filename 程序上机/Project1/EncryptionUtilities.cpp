#include "EncryptionUtilities.h"

    // �򵥵����ֶԳƼ��ܺ������������ڴ������ַ���
     string EncryptionUtilities::encryptDecrypt(const  string& input, int key) {
        string result = input;

        for (char& c : result) {
            if (isdigit(c)) { // �����������ַ�
                // '0' - '9' ��ASCIIֵ�� 48 - 57
                // ���ַ�ת��Ϊ0 - 9�����м��ܲ�������ת�����ַ�
                c = (c - '0' + key + 10) % 10 + '0';
            }
        }

        return result;
    }
