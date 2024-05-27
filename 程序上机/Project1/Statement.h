// Statement.h

#pragma once
#include <iostream>
#include <string>
using namespace std;
// ������ˮ��¼��
class Statement {
private:
     string ID;            // ��ˮ���
     string accountID;     // ��Ӧ�˻��Ŀ���
     string time;          // ����ʱ��
     int type;                  // �������ͣ�������ö�ٶ����������
     double amount;             // ���׽��
     string toAccountID;   // �Է��˻��Ŀ��ţ�ת��ʱʹ�ã�

public:
    // ���캯��
    Statement(const  string& id, const  string& accID, const  string& tm, int ty, double amt, const  string& toAccID);
    ~Statement();//��������
    // ��ȡ��ˮ���
    string getID() const;
    // ��ȡ�˻�����
     string getAccountID() const;
    // ��ȡ����ʱ��
     string getTime() const;
     int getType() const;
    // ��ȡ���׽��
    double getAmount() const;
    // ��ȡ�Է��˻�����
    string getToAccountID() const;

    // ������ˮ���
     void setID(const  string& newID);
    // �����˻�����
    void setAccountID(const  string& newAccountID);
    // ���ý���ʱ��
    void setTime(const  string& newTime);
    // ���ý�������
    void setType(int newType);
    // ���ý��׽��
    void setAmount(double newAmount);
    // ���öԷ��˻�����
    void setToAccountID(const  string& newToAccountID);

    // �˴��������������Ա����...
};

// ��������ö��
enum TransactionType {
    DEPOSIT = 1,   // ���
    WITHDRAWAL,    // ȡ��
    TRANSFER       // ת��
};