#include"Manage.h"
Manage::Manage()
{
}

Manage::~Manage()
{
}
// 获取当前时间函数实现
string Manage::getCurrentTime() {
    auto now = chrono::system_clock::now(); // 获取当前时间点
    auto nowTimeT = chrono::system_clock::to_time_t(now); // 转换为time_t
    tm localTime;

    // 使用localtime_s代替localtime
    localtime_s(&localTime, &nowTimeT);

    ostringstream oss;
    oss << put_time(&localTime, "%Y%m%d%H%M%S"); // 格式化输出
    return oss.str();
}

// 创建账户的函数
void Manage::createAccount() {
    string id, name, password;
    double balance;
    int key;
    cout << "请输入卡号: ";
    cin >> id;
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> password;
    cout << "请输入账户初始余额: ";
    cin >> balance;
    key = generateKey(id);
    // 创建账户实例
    Account newAccount(id, name, password, balance);

    // 写入文件
    if (FileHandler::writeAccountToFile(newAccount, key)) {
        cout << "账户创建成功！\n";
    }
    else {
        cout << "账户创建失败，请稍后再试。\n";
    }
}


// 验证登录的函数
bool Manage::verifyLogin(string id) {
    string  password;
    cout << "请输入密码: ";
    cin >> password;
    int key = generateKey(id);
    if (FileHandler::verifyAccountPassword(id, password, key)) {
        cout << "密码验证成功，欢迎登陆！\n";
        return true;
    }
    else {
        cout << "密码验证失败，卡号或密码错误。\n";
        return false;
    }
}

// 使用独立的存取款函数
void Manage::deposit(Account& account, double amount, int key) {
    
    double currentBalance = FileHandler::getAccountBalance(account.getID(), key);
    // 检查余额是否有效且存款额为正
    if (currentBalance >= 0 && amount > 0) {
        account.deposit(amount);
        FileHandler::updateAccountBalance(account.getID(), account.getBalance(), key);
        // 更新账户余额后再次创建并写入 Statement
        Statement depositStatement(getCurrentTime(), account.getID(),
            getCurrentTime(), TransactionType::DEPOSIT, amount, "self");
        FileHandler::writeStatementToFile(depositStatement,key);
    }
    else {
        cout << "存款失败。" << endl;
    }
}

void Manage::withdraw(Account& account, double amount, int key) {
    double currentBalance = FileHandler::getAccountBalance(account.getID(), key);
    // 检查取款金额是否合法
    if (currentBalance >= amount && amount > 0) {
        account.withdraw(amount);
        FileHandler::updateAccountBalance(account.getID(), account.getBalance(), key);
        // 更新账户余额后再次创建并写入 Statement
        Statement withdrawStatement(getCurrentTime(), account.getID(),
            getCurrentTime(), TransactionType::WITHDRAWAL, amount, "self");
        FileHandler::writeStatementToFile(withdrawStatement,key);
    }
    else {
        cout << (amount <= 0 ? "请输入有效的金额。\n" : "余额不足，取款失败。\n");
    }
}
// 查询余额
void Manage::queryBalance(const  string& accountId, int key) {
    // 调用 FileHandler 函数获取账户余额
    double balance = FileHandler::getAccountBalance(accountId, key);
    if (balance >= 0) {
        cout << "当前余额是：" << balance << endl;
    }
    else {
        cout << "查询余额失败。" << endl;
    }
}

//查询交易历史记录
void Manage::queryTransactionHistory(const  string& accountId, const int& key) {
    cout << "查询交易历史记录中...\n";
    // 调用 FileHandler 的方法来读取并打印交易记录
    FileHandler::readStatements(accountId,key);
}

void Manage::changePassword(const string &id,const int & key) {
    string oldPassword, newPassword;
    cout << "oldpassword:";
    cin >> oldPassword;
    cout << "newpassword:";
    cin >> newPassword;
    bool passwordChanged = FileHandler::updatePassword(id, oldPassword, newPassword, key);
    if (passwordChanged) {
        cout << "密码更新成功！" << endl;
    }
    else {
        cout << "密码更新失败。" << endl;
    }
}
// 转账函数
bool Manage::transfer(const  string& fromAccountId, const  string& toAccountId, double amount) {
    // 检索付款方账户
    int key1 = generateKey(fromAccountId);
    int key2 = generateKey(toAccountId);
    Account* fromAccount = FileHandler::retrieveAccountById(fromAccountId, key1);
    if (fromAccount == nullptr) {
        cerr << "付款方账户不存在。\n";
        return false;
    }

    // 检索收款方账户
    Account* toAccount = FileHandler::retrieveAccountById(toAccountId, key2);
    if (toAccount == nullptr) {
        cerr << "收款方账户不存在。\n";
        delete fromAccount; // 释放已分配的付款方资源
        return false;
    }

    // 执行转账
    if (fromAccount->withdraw(amount)) {
        if (toAccount->deposit(amount)) {
            // 更新两个账户的余额
            FileHandler::updateAccountBalance(fromAccount->getID(), fromAccount->getBalance(), key1);
            FileHandler::updateAccountBalance(toAccount->getID(), toAccount->getBalance(), key2);

            // 创建交易记录并写入文件
            Statement fromStatement(getCurrentTime(), fromAccountId, getCurrentTime(), TransactionType::TRANSFER, -amount, toAccountId);
            FileHandler::writeStatementToFile(fromStatement,key1);
            
            delete fromAccount; // 释放资源
            delete toAccount;
            cerr << "转账成功！\n";
            return true;
        }
        else {
            // 若收款方存款失败，回滚付款方的取款
            fromAccount->deposit(amount);
        }
    }

    // 清理资源
    delete fromAccount;
    delete toAccount;
    return false;
}
