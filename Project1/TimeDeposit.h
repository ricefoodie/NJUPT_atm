// TimeDeposit.h

#pragma once
#include "Account.h" //这里假设Account类已经存在

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
    // 添加获取利率的方法
    double getInterestRate() const {
        return interestRate;
    }

    // 添加获取存期的方法
    int getDepositTerm() const {
        return depositTerm;
    }

    // 其他有关定期存款的方法...
};