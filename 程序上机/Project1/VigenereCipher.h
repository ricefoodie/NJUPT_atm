
#include <iostream>
#include <string>
#include <cctype>

class VigenereCipher {
public:
    // 使用Vigenère加密算法对字符串进行加密
     string encrypt(const  string& plaintext, const  string& key) {
         string encryptedText = plaintext;  // Initialize with the plaintext

        for (size_t i = 0, j = 0; i < plaintext.length(); ++i) {
            if (isalpha(plaintext[i])) {  // Encrypt alphabetic characters
                bool isUpper = isupper(plaintext[i]);
                int alphaBase = isUpper ? 'A' : 'a';
                int keyShift = toupper(key[j % key.length()]) - 'A';

                encryptedText[i] = (plaintext[i] - alphaBase + keyShift) % 26 + alphaBase;
            }
            else if (isdigit(plaintext[i])) { // Encrypt numeric characters
                int numBase = '0';
                int keyShift = toupper(key[j % key.length()]) - 'A';

                encryptedText[i] = (plaintext[i] - numBase + keyShift) % 10 + numBase;
            }
            // Only increment j for alphanumeric characters to match Vigenère cipher behavior
            if (isalnum(plaintext[i])) j++;
        }

        return encryptedText;
    }

    // 使用Vigenère算法的逆过程解密字符串
     string decrypt(const  string& encryptedText, const  string& key) {
         string decryptedText = encryptedText;  // Initialize with the encrypted text

        for (size_t i = 0, j = 0; i < encryptedText.length(); ++i) {
            if (isalpha(encryptedText[i])) { // Decrypt alphabetic characters
                bool isUpper = isupper(encryptedText[i]);
                int alphaBase = isUpper ? 'A' : 'a';
                int keyShift = toupper(key[j % key.length()]) - 'A';

                decryptedText[i] = ((encryptedText[i] - alphaBase - keyShift + 26) % 26) + alphaBase;
            }
            else if (isdigit(encryptedText[i])) { // Decrypt numeric characters
                int numBase = '0';
                int keyShift = toupper(key[j % key.length()]) - 'A';

                decryptedText[i] = ((encryptedText[i] - numBase - keyShift + 10) % 10) + numBase;
            }
            // Only increment j for alphanumeric characters to match Vigenère cipher behavior
            if (isalnum(encryptedText[i])) j++;
        }

        return decryptedText;
    }
};

/*

int main() {
    VigenereCipher cipher;

    // 示例明文和密钥
     string plaintext = "Hello123World";
     string key = "VIGENERECIPHERKEY";

     cout << "Original text : " << plaintext << "\n";
     cout << "Key           : " << key << "\n";

    // 加密
     string encryptedText = cipher.encrypt(plaintext, key);
     cout << "Encrypted text: " << encryptedText << "\n";

    // 解密
     string decryptedText = cipher.decrypt(encryptedText, key);
     cout << "Decrypted text: " << decryptedText << "\n";

    return 0;
}*/