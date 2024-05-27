//Account.cpp
#include "Account.h"
//#include <iostream>
Account::Account(const string & id, const string & Name, const string & pw, double bal,int st)
{
    ID = id;          // ����
    name=Name;        // �û�����
    password=pw;    // �û����루�Ѽ��ܣ�
    balance=bal;          // �˻����
    state = st;      //�˻�״̬��0��ʾ������1��ʾ��ʼ״̬��2��3��4��5...��ʾ��¼����
}
Account::~Account() {}
// ��ȡ����
string Account::  getID() const { return ID; }
// ��ȡ�û�����
string Account:: getName() const { return name; }
// ��ȡ����
string Account::getPassword() const { return password; }
// ��ȡ�˻����
double Account::getBalance() const { return balance; }
// ��ȡ�˻�״̬
int Account::getState() const { return state; }

//����key
//int Account::generateKey(const  string& ID) {
//    int key;
//    key=stoi(ID)%10;
//	return key;
//}
// ���ÿ���
void Account::setID(const  string& newID) { ID = newID; }
// �����û�����
void Account::setName(const  string& newName) { name = newName; }
// ��������
void Account::setPassword(const  string& newPw) { password = newPw; }
// �����˻����
void Account::setBalance(double newBal) { balance = newBal; }
//����״̬
void Account::setState(int newSt) { state = newSt; }

// ����
bool Account::deposit(double amount) {
    if (amount > 0) {
        updateBalance(balance + amount); // ���� private ��Ա���������
        cout << "���ɹ�����ǰ��" << balance << endl;
        return true;
    }
    else {
        cout << "��������Ч�Ľ�\n";
        return false;
    }
}

// ȡ���
bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        updateBalance(balance - amount); // ���� private ��Ա���������
        cout << "ȡ��ɹ�����ǰ��" << balance << endl;
        return true;
    }
    else {
        cout << (amount <= 0 ? "��������Ч�Ľ�\n" : "���㣬ȡ��ʧ�ܡ�\n");
        return false;
    }
}

void Account::updateBalance(double newBalance) {
        balance = newBalance;
    }

int generateKey(const string& id) {
    int num = 0; // ��ʼ���������
    for (char c : id) { // �����ַ����е�ÿ���ַ�
        if (c >= '0' && c <= '9') { // ȷ���ַ�������
            num = num * 10 + (c - '0'); // ���½��������'0' �� '9' ���ַ��� 0 �� 9 ������ӳ��
        }

    }
    return 5; // ���ؽ��
}