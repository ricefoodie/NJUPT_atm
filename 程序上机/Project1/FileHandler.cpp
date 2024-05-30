//FileHander.cpp
#include "FileHandler.h"
#include <random>
#include <iomanip>
//将账户写入文件
bool FileHandler::writeAccountToFile(const Account& account, int key) {
    ofstream fileOut("accounts.dat", ios::app); // 使用追加模式
    if (!fileOut) {
        cerr << "无法打开文件写入。\n";
        return false;
    }
    fileOut << EncryptionUtilities::encryptDecrypt(account.getID(), key) << " "
        << account.getName() << " "
        << EncryptionUtilities::encryptDecrypt(account.getPassword(), key) << " "
        << account.getBalance() <<" " 
        <<account.getState() << endl;
    fileOut.close();
    return true;
}

// 从文件中读取账户信息并验证密码
bool FileHandler::verifyAccountPassword(const  string& id, const  string& password, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "无法打开文件读取。\n";
        return false;
    }

    string line;
    while (getline(fileIn, line)) {
        istringstream iss(line);
        string fileID, filePassword, fileName;
        double fileBalance;
        int fileState;
        if (iss >> fileID >> fileName >> filePassword >> fileBalance>>fileState) {
            if (fileID == EncryptionUtilities::encryptDecrypt(id, key) &&
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
bool FileHandler::updatePassword(const  string& id, const  string& oldPassword, const  string& newPassword, int key) {
    // 使用一个临时文件存储新的账户信息
    string tempFilename = "accounts_temp.dat";
    ifstream file("accounts.dat");
    ofstream tempFile(tempFilename);

    bool isUpdated = false;
    if (file.is_open() && tempFile.is_open()) {
        string fileID, fileName, filePassword;
        double fileBalance;
        int fileState;

        while (file >> fileID >> fileName >> filePassword >> fileBalance >> fileState) {
            if (fileID == EncryptionUtilities::encryptDecrypt(id, key)) {
                // 解密并比较密码
                string decryptedPassword = EncryptionUtilities::encryptDecrypt(filePassword, -key);
                if (decryptedPassword == oldPassword) {
                    // 若旧密码正确，使用新密码并加密后写入临时文件
                    isUpdated = true;
                    filePassword = EncryptionUtilities::encryptDecrypt(newPassword, key);
                }
                else {
                    // 旧密码不正确，不更新信息，返回失败
                    cerr << "旧密码不正确，无法更新。\n";
                    return false;
                }
            }
            // 将账户信息写入临时文件中
            tempFile << fileID << " " << fileName << " " << filePassword << " " << fileBalance << " "<<fileState<<"\n";
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
            cerr << "没有找到对应的账户进行更新。\n";
        }

    }
    else {
        cerr << "无法打开文件进行更新。\n";
        return false;
    }
    return isUpdated;
}
// 写入交易记录至文件
bool FileHandler::writeStatementToFile(const Statement& statement, const int& key) {
    ofstream fileOut("statements.dat", ios::app); // 使用追加模式打开交易流水记录文件
    if (!fileOut) {
        cerr << "无法打开文件写入交易记录。\n";
        return false;
    }

    // 存入交易信息，格式化为流水编号 账户卡号 交易时间 交易类型 交易金额 对方账户
    fileOut <<left<<setw(20)<< statement.getID() << setw(13)
        << EncryptionUtilities::encryptDecrypt(statement.getAccountID(), generateKey(statement.getAccountID())) << " "
        << statement.getTime() << setw(13)
        << statement.getType() << setw(13)
        << statement.getAmount() << setw(13)
        << EncryptionUtilities::encryptDecrypt(statement.getToAccountID(),generateKey(statement.getToAccountID())) << endl;
    fileOut.close();
    return true;
}

// 从文件中读取账户的所有交易流水记录
void FileHandler::readStatements(const  string& accountID,const int &key) {
    ifstream fileIn("statements.dat");
    if (!fileIn) {
        cerr << "无法打开文件读取交易记录。\n";
        return;
    }

    string line;
    cout <<left<< setw(20) << "流水编号"<< setw(20) << "账户卡号" << setw(20) << "交易时间" << setw(13) << "交易类型" << setw(13) << "交易金额" << setw(13) << "对方账户" << endl;
    int flag = -1;
    while (getline(fileIn, line)) {
        istringstream iss(line);
        string id, accID, time, toAccID;
        int type;
        double amount;
        //         流水编号 账户卡号 交易时间 交易类型 交易金额 对方账户
        if (iss >> id >> accID >> time >> type >> amount >> toAccID) {
            // cout << 1 <<  endl;
            
            if (EncryptionUtilities::encryptDecrypt(accID,-key) == accountID || EncryptionUtilities::encryptDecrypt(toAccID,-key)==accountID) {
                cout <<left<< setw(20)<< id << setw(20) << EncryptionUtilities::encryptDecrypt(accID, -key) << setw(20) << time << setw(13) << type << setw(13) << amount << setw(13) << EncryptionUtilities::encryptDecrypt(toAccID, -key) << endl;
                flag = 1;
            }
                                 
        }
    }
    if (flag != 1) {
        cout << "匹配错误" << endl;
    }
    fileIn.close();
}

// 更新账户余额
bool FileHandler::updateAccountBalance(const  string& id, double newBalance, int key) {
    ifstream fileIn("accounts.dat");
    ofstream fileOut("accounts_temp.dat");
    bool isUpdated = false;

    if (fileIn && fileOut) {
        string fileID, fileName, filePassword;
        double fileBalance;
        int fileState;
        while (fileIn >> fileID >> fileName >> filePassword >> fileBalance>>fileState) {
            if (fileID == EncryptionUtilities::encryptDecrypt(id, key)) {
                fileBalance = newBalance;  // 更新余额
                isUpdated = true;
            }
            fileOut << fileID
                << " " << fileName << " "
                << filePassword << " "
                << fileBalance << " "
                << fileState <<endl;
        }
        fileIn.close();
        fileOut.close();

        // 删除旧账户文件并将临时文件重命名为新账户文件
        remove("accounts.dat");
        rename("accounts_temp.dat", "accounts.dat");
    }
    else {
        cerr << "无法打开文件进行更新。\n";
        if (fileIn) fileIn.close();
        if (fileOut) {
            fileOut.close();
            remove("accounts_temp.dat");  // 删除临时文件
        }
        return false;
    }
    return isUpdated;
}

// 获取账户余额
double FileHandler::getAccountBalance(const  string& id, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "无法打开文件来获取余额。\n";
        return -1; // 使用错误值表示无法获取余额
    }

    string fileID, fileName, filePassword;
    double fileBalance;
    int fileState;
    while (fileIn >> fileID >> fileName >> filePassword >> fileBalance >> fileState) {
        if (fileID == EncryptionUtilities::encryptDecrypt(id, key)) {
            fileIn.close();
            return fileBalance; // 返回解密后的账户余额
        }
    }
    fileIn.close();
    cerr << "没找到对应的账户余额。\n";
    return -1; // 使用错误值表示账户不存在
}

// 获取账户状态
int FileHandler::getAccountState(const  string& id, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "无法打开文件来获取状态。\n";
        return -1; // 使用错误值表示无法获取状态
    }

    string fileID, fileName, filePassword;
    double fileBalance;
    int fileState;
    while (fileIn >> fileID >> fileName >> filePassword >> fileBalance >> fileState) {
        if (fileID == EncryptionUtilities::encryptDecrypt(id, key)) {
            fileIn.close();
            return fileState; // 返回账户状态
        }
    }
    fileIn.close();
    cerr << "没找到对应的账户余额。\n";
    return -1; // 使用错误值表示账户不存在
}

//更新状态
bool FileHandler::updateAccountState(const  string& id, int newState, int key) {
    ifstream fileIn("accounts.dat");
    ofstream fileOut("accounts_temp.dat");
    bool isUpdated = false;

    if (fileIn && fileOut) {
        string fileID, fileName, filePassword;
        double fileBalance;
        int fileState;
        while (fileIn >> fileID >> fileName >> filePassword >> fileBalance >> fileState) {
            if (fileID == EncryptionUtilities::encryptDecrypt(id, key)) {
                fileState = newState;  // 更新状态
                isUpdated = true;
            }
            fileOut << fileID
                << " " << fileName << " "
                << filePassword << " "
                << fileBalance << " "
                << fileState << endl;
        }
        fileIn.close();
        fileOut.close();

        // 删除旧账户文件并将临时文件重命名为新账户文件
        remove("accounts.dat");
        rename("accounts_temp.dat", "accounts.dat");
    }
    else {
        cerr << "无法打开文件进行更新。\n";
        if (fileIn) fileIn.close();
        if (fileOut) {
            fileOut.close();
            remove("accounts_temp.dat");  // 删除临时文件
        }
        return false;
    }
    return isUpdated;
}


// 按ID检索账户信息
Account* FileHandler::retrieveAccountById(const  string& id, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "无法打开文件读取账户信息。\n";
        return nullptr; // 返回 nullptr 表示没找到账户
    }

    string fileID, fileName, filePassword;
    double fileBalance;
    int fileState;
    while (fileIn >> fileID >> fileName >> filePassword >> fileBalance>> fileState) {
        // 解密并检查ID是否匹配
        if (EncryptionUtilities::encryptDecrypt(fileID, -key) == id) {
            fileIn.close();
            // 返回动态分配的对应的账户对象
            return new Account(id, fileName, filePassword, fileBalance,fileState);
        }
    }

    fileIn.close();
    cerr << "未找到匹配的账户ID。\n";
    return nullptr; // 未找到账户，返回 nullptr
}
//#include "FileHandler.h"


// 使用提供的key解密ID，并根据是否是被转账方反向累加指定用户ID的所有交易金额
// 然后在这个基数上加上一个范围在-100到+100的随机数
double FileHandler::getRandomizedSumByAccountId(const string& id, int key,int amplitude) {//振幅
    ifstream fileIn("statements.dat");
    if (!fileIn) {
        cerr << "无法打开文件来计算总和。\n";
        return -1; // 使用错误值表示无法进行计算
    }

    string line;
    double totalAmountForAccountID = 0.0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-amplitude,amplitude); // 定义-100到100的均匀分布

    while (getline(fileIn, line)) {
        istringstream iss(line);
        string id, encAccountID, time, encToAccountID;
        int type;
        double amount;
        // 假设数据格式为: 流水编号 加密账户卡号 交易时间 交易类型 交易金额 对方加密账户
        if (iss >> id >> encAccountID >> time >> type >> amount >> encToAccountID) {
            // 对于发起方账户，直接累加金额
            if (EncryptionUtilities::encryptDecrypt(encAccountID, key) == id) {
                totalAmountForAccountID += amount;
            }
            // 对于接收方账户，累加金额的相反数
            else if (EncryptionUtilities::encryptDecrypt(encToAccountID, key) == id) {
                totalAmountForAccountID -= amount;
            }
        }
    }
    fileIn.close();

    // 在累计金额基础上加上随机数
    totalAmountForAccountID += distr(gen);

    return totalAmountForAccountID; // 返回随机化后的总金额
}


// 其他需要的类定义和函数声明...

void  FileHandler::printAllAccountInfo() {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "无法打开文件读取账户信息。\n";
        return;
    }

    cout <<left << setw(15) << "账户卡号"<< setw(15) << "用户姓名" << setw(10) << "用户密码" << setw(10) << "账户余额" << setw(10) << " 账户状态" << endl;

    string encID, Name, encPassword;
    double fileBalance;
    int fileState;

    while (fileIn >> encID >> Name >> encPassword >> fileBalance >> fileState) {
        // 使用账户ID获取相关的密钥
        int key = generateKey(encID); // 根据ID产生key

        // 解密ID和密码
        string decryptedID = EncryptionUtilities::encryptDecrypt(encID, -key);
      //  string decryptedName = EncryptionUtilities::encryptDecrypt(encName, key);
        string decryptedPassword = EncryptionUtilities::encryptDecrypt(encPassword, -key);

        // 输出解密后的信息
        cout<<left<< setw(15)<<decryptedID << setw(15)
            << Name << setw(10)
            << decryptedPassword << setw(10)
            << fileBalance << setw(10)
            << fileState <<endl;
    }

    fileIn.close();
}

//写入定期存款账户
/*bool FileHandler::writeTimeDepositAccountToFile(const TimeDepositAccount& account, int key) {
    // 打开定期存款文件
    ofstream outFile("time_deposits.dat", ios::app | ios::binary);
    if (!outFile) {
        cout << "文件打开失败" << endl;
        return false;
    }
    // 写入账户信息
    outFile << EncryptionUtilities::encryptDecrypt(account.getID(), generateKey(account.getID())) << "\t"
        << account.getName() << "\t"
        << EncryptionUtilities::encryptDecrypt(account.getPassword(), generateKey(account.getID())) << "\t"
        << account.getBalance() << "\t"
        << account.getInterestRate() << "\t"
        << account.getDepositTerm() << endl;
    outFile.close();
    return true;
}*/
