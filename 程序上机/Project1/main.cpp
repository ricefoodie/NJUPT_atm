// main.cpp
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
#include"Manage.h"
#include <Windows.h>
using namespace std;

int generateKey(const string &id);
int main() {
    Manage atm_manager;
    StartMenu:
        cout << endl;
  while(1){
      bool flag2 = true;
     cout << "ATM系统\n";
     cout << "0. 退出\n";
     cout << "1. 管理员\n";
     cout << "2. 用户\n";
     cout << "请选择一个选项: ";
     int option=-1;
     while (option < 0 || option>2) {
         cin >> option;
         if (option < 0 || option>2) {
             cout << "请重新输入" << endl;
         }
     }
     int managepassword = 123456, inputpassword;
     switch (option) {
     case 1:
         cout << "请输入管理员密码：" ;
         cin >> inputpassword;
         while (inputpassword != managepassword) {
             cout << "错误！请重试,或输入0回到主页面"<<endl;
             cin >> inputpassword;
             if (inputpassword == 0){
                 goto StartMenu;
             }
             
         }
         cout <<endl<< "管理员登录成功\n1.用户信息" << endl;
         cout << "2.创建用户" << endl;
         cout << "3.创建定期存款账户" << endl;
         cout << "0.返回" << endl;
         while (flag2) {
         int option3;
         cin >> option3;
         switch (option3) {
         case 1: { 
             FileHandler::printAllAccountInfo();
             cout << "\n\n1.检索特定用户" << endl;
             cout << "2.更改用户状态" << endl;
             cout << "0.返回" << endl;
             int option4;
             int key = 5;
             string id;
             cin >> option4;
             switch (option4) {
             case 1:
                 cout << "\n输入需要检索的用户ID" << endl;
                 cin >> id;
                 atm_manager.queryTransactionHistory(id, key);
                 break;
             case 2:
                 cout << "\n用户ID" << endl;
                 cin >> id;
                 FileHandler::updateAccountState(id, 1, key);
                 cout << "已解锁" << endl;
                 break;
             case 0:break;
             }
             break; 
         }
         case 2: {
             atm_manager.createAccount();
             break;
         }
         case 3: {
             atm_manager.createTimeDepositAccount();
             break;
         }
         case 0:flag2 = false; break;
         }
     }break;
         
     case 2:
     {
         int loginAttempts = 0;//登录错误计数器
         string id;
         int key;
         Account* currentAccount;
         
         do {
             cout << "请输入正确的卡号,或输入0回到主页面:";
             cin >> id;
             if (id == "0") {
                 goto StartMenu;
             }
             key = generateKey(id);            
             currentAccount = FileHandler::retrieveAccountById(id, key);

         } while (currentAccount == nullptr);
         if (FileHandler::getAccountState(id,key) == 0) {
             cout << "已锁卡，联系管理员解决！" << endl;
             break;
         }
             
         while (!(atm_manager.verifyLogin(id))) {//先登录
             loginAttempts++;

             if (loginAttempts < 3) {
                 cout << "密码输入错误，你已经输错了 " << loginAttempts << " 次，还剩" << 3 - loginAttempts << "次机会！" << endl;
             }
             else {
                 cout << "锁卡！" << endl;
                 FileHandler::updateAccountState(id,0,key);
                 return 1; // 退出程序
             }
         }
         //到这里已经成功登录  
         FileHandler::updateAccountState(id, FileHandler::getAccountState(id, key)+1, key);
         if (FileHandler::getAccountState(id, key) >= 5)
         {
             cout << "账户安全检查：检测到您已经多次登录没有修改密码，建议修改密码\n\n";
             Sleep(2500);
         }
         cout << "ATM系统\n";
         cout << "0. 返回\n";
         cout << "1. 存款\n";
         cout << "2. 取款\n";
         cout << "3. 转账\n";
         cout << "4. 余额查询\n";
         cout << "5. 历史交易查询\n";
         cout << "6. 修改密码\n";
         cout << "7. 预测余额\n";
      //   cout << "8. 创建定期存款账户\n";
         cout << "8. 货币兑换" << endl;
         bool flag = true;
         while (flag) {
             cout << "请选择一个选项: ";
             int option2;
             char yn;
             cin >> option2;
             switch (option2) {
             case 1: {   // 存款
                 double depositAmount;
                 cout << "请输入存款金额:";
                 cin >> depositAmount;
                 atm_manager.deposit(*currentAccount, depositAmount, key);  // 使用存款函数
                 cout << "是否打印回单？y/n" << endl;
                 cin >> yn;
                 if (yn == 'y')
                     cout << "打印成功！";
                 break;
             }
             case 2: {   // 取款
                 double withdrawAmount;
                 cout << "请输入取款金额:";
                 cin >> withdrawAmount;
                 atm_manager.withdraw(*currentAccount, withdrawAmount, key);  // 使用取款函数
                 cout << "是否打印回单？y/n" << endl;
                 cin >> yn;
                 if (yn == 'y')
                     cout << "打印成功！";
                 break;
             }
             case 3: {
                 string  toAccountId;
                 double amount;
                 cout << "请输入收款方账号: ";
                 cin >> toAccountId;
                 cout << "请输入转账金额: ";
                 cin >> amount;

                 // 执行转账
                 bool success = atm_manager.transfer(id, toAccountId, amount);
                 if (success) {
                     cout << "转账成功。\n";
                     cout << "是否打印回单？y/n" << endl;
                     cin >> yn;
                     if (yn == 'y')
                         cout << "打印成功！";
                 }
                 else {
                     cout << "转账失败。\n";
                 }
             }
             case 4: {//余额查询
                 atm_manager.queryBalance(id, key);
                 break;
             }
             case 5: {//查询交易历史记录
                 atm_manager.queryTransactionHistory(id, key);
                 break;
             }
             case 6: {//修改密码
                 atm_manager.changePassword(id, key);
                 break;
             }
             case 7: {
             atm_manager.predictBal(id,key, currentAccount->getBalance());
             break;
             }
             case 8: {
             cout<<"请输入需要兑换的货币种类：（直接存到账户）"<<endl;
             cout << "1.美元->人民币，2.英镑->人民币，3.欧元->人民币" << endl;
             int cointype;
             cin >> cointype;
             double depositAmount;
             cout << "请输入兑换金额:";
             cin >> depositAmount;
             
             switch (cointype) {
             case 1:depositAmount *= 7.24;    break;
             case 2:depositAmount *= 9.03;    break;
             case 3:depositAmount *= 7.73;    break;
             default:cout << "输入有误，请重新输入。" << endl; break;
             }
             atm_manager.deposit(*currentAccount, depositAmount, key);  // 使用存款函数
             cout << "是否打印回单？y/n" << endl;
             cin >> yn;
             if (yn == 'y')
                 cout << "打印成功！";
             break;
             }
             case 0: {//返回
                 flag = false;
                 cout<< "返回成功,请重新输入选项" << endl;
                 
                 break;
             }
             default: {
                 cout << "输入有误，请重新输入" << endl;
                 break;
             }
             }
         }break;
     }
     case 0: {
           cout << "系统已退出，请保存好您的银行卡" << endl;
           exit(0);
           break;}
     default: {
         cout << "输入有误，请重新输入" << endl;
         break;
     }
    }
}
    return 0;
}




