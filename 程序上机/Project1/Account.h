// Account.h

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
// �û��˻���Ϣ��
class Account {
public:
    string ID;          // ����
    string name;        // �û�����
    string password;    // �û����루�Ѽ��ܣ�
    double balance;          // �˻����
    int state;      //�˻�״̬��0��ʾ������1��ʾ��ʼ״̬��2��3��ʾ��¼����
public:
    // ���캯��
    Account(const  string& id, const  string& Name, const  string& pw, double bal,int state);
    ~Account();//��������

    // ��ȡ����
    string getID() const;
    // ��ȡ�û�����
    string getName() const;
    // ��ȡ����
    string getPassword() const;
    // ��ȡ�˻����
    double getBalance() const;
    //��ȡ״̬
    int getState() const;
    //����key
   // static int generateKey(const  string& ID);
    // ���ÿ���
    void setID(const  string& newID);
    // �����û�����
    void setName(const  string& newName);
    // ��������
    void setPassword(const  string& newPw);
    // �����˻����
    void setBalance(double newBal);
    //����״̬
    void setState(int newSt);

    // ����
    bool deposit(double amount);

    // ȡ���
    bool withdraw(double amount);
    //double predictBal(string id);
private:
    void updateBalance(double newBalance);

};
int generateKey(const  string& id);