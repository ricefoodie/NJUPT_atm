// FileHandler.h

#pragma once

#include "Account.h"
#include "EncryptionUtilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Statement.h"
#include "TimeDeposit.h"
using namespace std;
class FileHandler {

public:
    
    // д���˻���Ϣ���ļ�
    static bool writeAccountToFile(const Account& account, int key);

    // ���ļ��ж�ȡ�˻���Ϣ����֤����
    static bool verifyAccountPassword(const  string& id, const  string& password, int key);
    // �����˻�����
    static bool updatePassword(const  string& id, const  string& oldPassword,
        const  string& newPassword, int key);
    // д�뽻�׼�¼���ļ�
    static bool writeStatementToFile(const Statement& statement, const int& key);

    // ���ļ��ж�ȡ�˻������н�����ˮ��¼
    static void readStatements(const  string& accountID, const int& key);

    // �����˻����
    static bool updateAccountBalance(const  string& id, double newBalance, int key);

    // ��ȡ�˻����
    static double getAccountBalance(const  string& id, int key);
    
    // �����˻�״̬
    static bool updateAccountState(const  string& id, int newState, int key);

    //��ȡ�˻�״̬
    static int getAccountState(const  string& id, int key);

    // ��ID�����˻���Ϣ
    static Account* retrieveAccountById(const  string& id, int key);

    static double getRandomizedSumByAccountId(const string& id, int key, int amplitude);

    //��ӡ�����˻���Ϣ
    static void printAllAccountInfo();

    //д�붨�ڴ���˻�
    static bool writeTimeDepositAccountToFile(const TimeDepositAccount& account, int key);
};


