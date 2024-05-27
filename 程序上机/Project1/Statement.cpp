#include "Statement.h"
  
Statement::Statement(const  string& id, const  string& accID,
        const  string& tm, int ty, double amt, const  string& toAccID)
    {    
        ID=id;            // 流水编号
        accountID=accID;     // 对应账户的卡号
        time=tm;          // 交易时间
        type=ty;                  // 交易类型，可以用枚举定义具体类型
        amount=amt;             // 交易金额
        toAccountID=toAccID;   // 对方账户的卡号（转账时使用）
    }
Statement::~Statement() {}
    // 获取流水编号
string Statement::getID() const { return ID; }
    // 获取账户卡号
string Statement::getAccountID() const { return accountID; }
    // 获取交易时间
string Statement::getTime() const { return time; }
    // 获取交易类型
int Statement::getType() const { return type; }
    // 获取交易金额
double Statement::getAmount() const { return amount; }
    // 获取对方账户卡号
string Statement::getToAccountID() const { return toAccountID; }

    // 设置流水编号
void Statement::setID(const  string& newID) { ID = newID; }
    // 设置账户卡号
void Statement::setAccountID(const  string& newAccountID) { accountID = newAccountID; }
    // 设置交易时间
void Statement::setTime(const  string& newTime) { time = newTime; }
    // 设置交易类型
void Statement::setType(int newType) { type = newType; }
    // 设置交易金额
void Statement::setAmount(double newAmount) { amount = newAmount; }
    // 设置对方账户卡号
void Statement::setToAccountID(const  string& newToAccountID) { toAccountID = newToAccountID; }

    // 此处可以添加其他成员函数...


