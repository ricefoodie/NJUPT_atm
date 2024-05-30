//FileHander.cpp
#include "FileHandler.h"
#include <random>
#include <iomanip>
//���˻�д���ļ�
bool FileHandler::writeAccountToFile(const Account& account, int key) {
    ofstream fileOut("accounts.dat", ios::app); // ʹ��׷��ģʽ
    if (!fileOut) {
        cerr << "�޷����ļ�д�롣\n";
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

// ���ļ��ж�ȡ�˻���Ϣ����֤����
bool FileHandler::verifyAccountPassword(const  string& id, const  string& password, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "�޷����ļ���ȡ��\n";
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
// �����˻�����
bool FileHandler::updatePassword(const  string& id, const  string& oldPassword, const  string& newPassword, int key) {
    // ʹ��һ����ʱ�ļ��洢�µ��˻���Ϣ
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
                // ���ܲ��Ƚ�����
                string decryptedPassword = EncryptionUtilities::encryptDecrypt(filePassword, -key);
                if (decryptedPassword == oldPassword) {
                    // ����������ȷ��ʹ�������벢���ܺ�д����ʱ�ļ�
                    isUpdated = true;
                    filePassword = EncryptionUtilities::encryptDecrypt(newPassword, key);
                }
                else {
                    // �����벻��ȷ����������Ϣ������ʧ��
                    cerr << "�����벻��ȷ���޷����¡�\n";
                    return false;
                }
            }
            // ���˻���Ϣд����ʱ�ļ���
            tempFile << fileID << " " << fileName << " " << filePassword << " " << fileBalance << " "<<fileState<<"\n";
        }

        file.close();
        tempFile.close();

        if (isUpdated) {
            // ʹ���µ��˻��ļ��滻�ɵ��ļ�
            remove("accounts.dat");
            rename(tempFilename.c_str(), "accounts.dat");
        }
        else {
            // ��û�и����κ����ݣ�ɾ����ʱ�ļ�
            remove(tempFilename.c_str());
            cerr << "û���ҵ���Ӧ���˻����и��¡�\n";
        }

    }
    else {
        cerr << "�޷����ļ����и��¡�\n";
        return false;
    }
    return isUpdated;
}
// д�뽻�׼�¼���ļ�
bool FileHandler::writeStatementToFile(const Statement& statement, const int& key) {
    ofstream fileOut("statements.dat", ios::app); // ʹ��׷��ģʽ�򿪽�����ˮ��¼�ļ�
    if (!fileOut) {
        cerr << "�޷����ļ�д�뽻�׼�¼��\n";
        return false;
    }

    // ���뽻����Ϣ����ʽ��Ϊ��ˮ��� �˻����� ����ʱ�� �������� ���׽�� �Է��˻�
    fileOut <<left<<setw(20)<< statement.getID() << setw(13)
        << EncryptionUtilities::encryptDecrypt(statement.getAccountID(), generateKey(statement.getAccountID())) << " "
        << statement.getTime() << setw(13)
        << statement.getType() << setw(13)
        << statement.getAmount() << setw(13)
        << EncryptionUtilities::encryptDecrypt(statement.getToAccountID(),generateKey(statement.getToAccountID())) << endl;
    fileOut.close();
    return true;
}

// ���ļ��ж�ȡ�˻������н�����ˮ��¼
void FileHandler::readStatements(const  string& accountID,const int &key) {
    ifstream fileIn("statements.dat");
    if (!fileIn) {
        cerr << "�޷����ļ���ȡ���׼�¼��\n";
        return;
    }

    string line;
    cout <<left<< setw(20) << "��ˮ���"<< setw(20) << "�˻�����" << setw(20) << "����ʱ��" << setw(13) << "��������" << setw(13) << "���׽��" << setw(13) << "�Է��˻�" << endl;
    int flag = -1;
    while (getline(fileIn, line)) {
        istringstream iss(line);
        string id, accID, time, toAccID;
        int type;
        double amount;
        //         ��ˮ��� �˻����� ����ʱ�� �������� ���׽�� �Է��˻�
        if (iss >> id >> accID >> time >> type >> amount >> toAccID) {
            // cout << 1 <<  endl;
            
            if (EncryptionUtilities::encryptDecrypt(accID,-key) == accountID || EncryptionUtilities::encryptDecrypt(toAccID,-key)==accountID) {
                cout <<left<< setw(20)<< id << setw(20) << EncryptionUtilities::encryptDecrypt(accID, -key) << setw(20) << time << setw(13) << type << setw(13) << amount << setw(13) << EncryptionUtilities::encryptDecrypt(toAccID, -key) << endl;
                flag = 1;
            }
                                 
        }
    }
    if (flag != 1) {
        cout << "ƥ�����" << endl;
    }
    fileIn.close();
}

// �����˻����
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
                fileBalance = newBalance;  // �������
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

        // ɾ�����˻��ļ�������ʱ�ļ�������Ϊ���˻��ļ�
        remove("accounts.dat");
        rename("accounts_temp.dat", "accounts.dat");
    }
    else {
        cerr << "�޷����ļ����и��¡�\n";
        if (fileIn) fileIn.close();
        if (fileOut) {
            fileOut.close();
            remove("accounts_temp.dat");  // ɾ����ʱ�ļ�
        }
        return false;
    }
    return isUpdated;
}

// ��ȡ�˻����
double FileHandler::getAccountBalance(const  string& id, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "�޷����ļ�����ȡ��\n";
        return -1; // ʹ�ô���ֵ��ʾ�޷���ȡ���
    }

    string fileID, fileName, filePassword;
    double fileBalance;
    int fileState;
    while (fileIn >> fileID >> fileName >> filePassword >> fileBalance >> fileState) {
        if (fileID == EncryptionUtilities::encryptDecrypt(id, key)) {
            fileIn.close();
            return fileBalance; // ���ؽ��ܺ���˻����
        }
    }
    fileIn.close();
    cerr << "û�ҵ���Ӧ���˻���\n";
    return -1; // ʹ�ô���ֵ��ʾ�˻�������
}

// ��ȡ�˻�״̬
int FileHandler::getAccountState(const  string& id, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "�޷����ļ�����ȡ״̬��\n";
        return -1; // ʹ�ô���ֵ��ʾ�޷���ȡ״̬
    }

    string fileID, fileName, filePassword;
    double fileBalance;
    int fileState;
    while (fileIn >> fileID >> fileName >> filePassword >> fileBalance >> fileState) {
        if (fileID == EncryptionUtilities::encryptDecrypt(id, key)) {
            fileIn.close();
            return fileState; // �����˻�״̬
        }
    }
    fileIn.close();
    cerr << "û�ҵ���Ӧ���˻���\n";
    return -1; // ʹ�ô���ֵ��ʾ�˻�������
}

//����״̬
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
                fileState = newState;  // ����״̬
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

        // ɾ�����˻��ļ�������ʱ�ļ�������Ϊ���˻��ļ�
        remove("accounts.dat");
        rename("accounts_temp.dat", "accounts.dat");
    }
    else {
        cerr << "�޷����ļ����и��¡�\n";
        if (fileIn) fileIn.close();
        if (fileOut) {
            fileOut.close();
            remove("accounts_temp.dat");  // ɾ����ʱ�ļ�
        }
        return false;
    }
    return isUpdated;
}


// ��ID�����˻���Ϣ
Account* FileHandler::retrieveAccountById(const  string& id, int key) {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "�޷����ļ���ȡ�˻���Ϣ��\n";
        return nullptr; // ���� nullptr ��ʾû�ҵ��˻�
    }

    string fileID, fileName, filePassword;
    double fileBalance;
    int fileState;
    while (fileIn >> fileID >> fileName >> filePassword >> fileBalance>> fileState) {
        // ���ܲ����ID�Ƿ�ƥ��
        if (EncryptionUtilities::encryptDecrypt(fileID, -key) == id) {
            fileIn.close();
            // ���ض�̬����Ķ�Ӧ���˻�����
            return new Account(id, fileName, filePassword, fileBalance,fileState);
        }
    }

    fileIn.close();
    cerr << "δ�ҵ�ƥ����˻�ID��\n";
    return nullptr; // δ�ҵ��˻������� nullptr
}
//#include "FileHandler.h"


// ʹ���ṩ��key����ID���������Ƿ��Ǳ�ת�˷������ۼ�ָ���û�ID�����н��׽��
// Ȼ������������ϼ���һ����Χ��-100��+100�������
double FileHandler::getRandomizedSumByAccountId(const string& id, int key,int amplitude) {//���
    ifstream fileIn("statements.dat");
    if (!fileIn) {
        cerr << "�޷����ļ��������ܺ͡�\n";
        return -1; // ʹ�ô���ֵ��ʾ�޷����м���
    }

    string line;
    double totalAmountForAccountID = 0.0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-amplitude,amplitude); // ����-100��100�ľ��ȷֲ�

    while (getline(fileIn, line)) {
        istringstream iss(line);
        string id, encAccountID, time, encToAccountID;
        int type;
        double amount;
        // �������ݸ�ʽΪ: ��ˮ��� �����˻����� ����ʱ�� �������� ���׽�� �Է������˻�
        if (iss >> id >> encAccountID >> time >> type >> amount >> encToAccountID) {
            // ���ڷ����˻���ֱ���ۼӽ��
            if (EncryptionUtilities::encryptDecrypt(encAccountID, key) == id) {
                totalAmountForAccountID += amount;
            }
            // ���ڽ��շ��˻����ۼӽ����෴��
            else if (EncryptionUtilities::encryptDecrypt(encToAccountID, key) == id) {
                totalAmountForAccountID -= amount;
            }
        }
    }
    fileIn.close();

    // ���ۼƽ������ϼ��������
    totalAmountForAccountID += distr(gen);

    return totalAmountForAccountID; // �������������ܽ��
}


// ������Ҫ���ඨ��ͺ�������...

void  FileHandler::printAllAccountInfo() {
    ifstream fileIn("accounts.dat");
    if (!fileIn) {
        cerr << "�޷����ļ���ȡ�˻���Ϣ��\n";
        return;
    }

    cout <<left << setw(15) << "�˻�����"<< setw(15) << "�û�����" << setw(10) << "�û�����" << setw(10) << "�˻����" << setw(10) << " �˻�״̬" << endl;

    string encID, Name, encPassword;
    double fileBalance;
    int fileState;

    while (fileIn >> encID >> Name >> encPassword >> fileBalance >> fileState) {
        // ʹ���˻�ID��ȡ��ص���Կ
        int key = generateKey(encID); // ����ID����key

        // ����ID������
        string decryptedID = EncryptionUtilities::encryptDecrypt(encID, -key);
      //  string decryptedName = EncryptionUtilities::encryptDecrypt(encName, key);
        string decryptedPassword = EncryptionUtilities::encryptDecrypt(encPassword, -key);

        // ������ܺ����Ϣ
        cout<<left<< setw(15)<<decryptedID << setw(15)
            << Name << setw(10)
            << decryptedPassword << setw(10)
            << fileBalance << setw(10)
            << fileState <<endl;
    }

    fileIn.close();
}

//д�붨�ڴ���˻�
/*bool FileHandler::writeTimeDepositAccountToFile(const TimeDepositAccount& account, int key) {
    // �򿪶��ڴ���ļ�
    ofstream outFile("time_deposits.dat", ios::app | ios::binary);
    if (!outFile) {
        cout << "�ļ���ʧ��" << endl;
        return false;
    }
    // д���˻���Ϣ
    outFile << EncryptionUtilities::encryptDecrypt(account.getID(), generateKey(account.getID())) << "\t"
        << account.getName() << "\t"
        << EncryptionUtilities::encryptDecrypt(account.getPassword(), generateKey(account.getID())) << "\t"
        << account.getBalance() << "\t"
        << account.getInterestRate() << "\t"
        << account.getDepositTerm() << endl;
    outFile.close();
    return true;
}*/
