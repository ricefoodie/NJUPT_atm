//Manage.h
#pragma once
#include <windows.h>
#include "Account.h"
#include "Statement.h"
#include <fstream>
#include <iostream>
#include "FileHandler.h"
#include <limits>
#include <string>
#include <cctype>
#include <chrono>   
#include <ctime>    
#include <sstream>  
#include <iomanip>
#include <conio.h>
using namespace std;
class Manage
{
public:
	Manage();
	~Manage();
	// ��ȡ��ǰʱ�亯��ʵ��
    string getCurrentTime();

// �����˻��ĺ���
    void createAccount();

// �������ڴ���˻��ĺ���
    void createTimeDepositAccount();

// ��֤��¼�ĺ���
    bool verifyLogin(string id);

// ʹ�ö����Ĵ�ȡ���
    void deposit(Account& account, double amount, int key);

    void withdraw(Account& account, double amount, int key);
// ��ѯ���
    void queryBalance(const  string& accountId, int key);
    void changePassword(const string& id, const int& key);
//��ѯ������ʷ��¼
    void queryTransactionHistory(const  string& accountId, const int& key);
    double predictBal(const string& id, int key, double bal);


bool transfer(const  string& fromAccountId, const  string& toAccountId, double amount);



};

