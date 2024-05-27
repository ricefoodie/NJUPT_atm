// TimeDeposit.h

#pragma once
#include "Account.h" //�������Account���Ѿ�����

class TimeDepositAccount : public Account {
private:
    double interestRate;
    int depositTerm;
public:
    TimeDepositAccount(const string& id, const string& name, const string& pw,
        double bal, double interest, int term, int st)
        : Account(id, name, pw, bal, st), interestRate(interest), depositTerm(term) {}

    double calculateInterest() {
        double receiveBalance = getBalance();
        return (receiveBalance * interestRate * depositTerm / 365);
    }
    // ��ӻ�ȡ���ʵķ���
    double getInterestRate() const {
        return interestRate;
    }

    // ��ӻ�ȡ���ڵķ���
    int getDepositTerm() const {
        return depositTerm;
    }

    // �����йض��ڴ��ķ���...
};