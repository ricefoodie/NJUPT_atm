#include "Statement.h"
  
Statement::Statement(const  string& id, const  string& accID,
        const  string& tm, int ty, double amt, const  string& toAccID)
    {    
        ID=id;            // ��ˮ���
        accountID=accID;     // ��Ӧ�˻��Ŀ���
        time=tm;          // ����ʱ��
        type=ty;                  // �������ͣ�������ö�ٶ����������
        amount=amt;             // ���׽��
        toAccountID=toAccID;   // �Է��˻��Ŀ��ţ�ת��ʱʹ�ã�
    }
Statement::~Statement() {}
    // ��ȡ��ˮ���
string Statement::getID() const { return ID; }
    // ��ȡ�˻�����
string Statement::getAccountID() const { return accountID; }
    // ��ȡ����ʱ��
string Statement::getTime() const { return time; }
    // ��ȡ��������
int Statement::getType() const { return type; }
    // ��ȡ���׽��
double Statement::getAmount() const { return amount; }
    // ��ȡ�Է��˻�����
string Statement::getToAccountID() const { return toAccountID; }

    // ������ˮ���
void Statement::setID(const  string& newID) { ID = newID; }
    // �����˻�����
void Statement::setAccountID(const  string& newAccountID) { accountID = newAccountID; }
    // ���ý���ʱ��
void Statement::setTime(const  string& newTime) { time = newTime; }
    // ���ý�������
void Statement::setType(int newType) { type = newType; }
    // ���ý��׽��
void Statement::setAmount(double newAmount) { amount = newAmount; }
    // ���öԷ��˻�����
void Statement::setToAccountID(const  string& newToAccountID) { toAccountID = newToAccountID; }

    // �˴��������������Ա����...


