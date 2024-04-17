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
using namespace std;

int generateKey(const string &id);
int main() {
    Manage atm_manager;
  while(1){
      bool flag2 = true;
     cout << "ATM系统\n";
     cout << "0. 退出\n";
     cout << "1. 管理员\n";
     cout << "2. 用户\n";
     cout << "请选择一个选项: ";
     int option;
     cin >> option;
     switch (option) {
         
     case 1:
         
         cout << "1.用户信息" << endl;
         cout << "2.创建用户" << endl;
         cout << "0.返回" << endl;
         while (flag2) {
         int option3;
         cin >> option3;
         switch (option3) {
         case 1:break;
         case 2: {
             atm_manager.createAccount();
             break;
         };
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
             cout << "请输入正确的卡号: ";
             cin >> id;
             key = generateKey(id);            
             currentAccount = FileHandler::retrieveAccountById(id, key);

         } while (currentAccount == nullptr);
         
         while (!(atm_manager.verifyLogin(id))) {//先登录
             loginAttempts++;

             if (loginAttempts < 3) {
                 cout << "密码输入错误，你已经输错了 " << loginAttempts << " 次，还剩" << 3 - loginAttempts << "次机会！" << endl;
             }
             else {
                 cout << "锁卡！" << endl;
                 // 这里可以添加锁定账户或卡的逻辑
                 return 1; // 退出程序或按需要处理。
             }
         }
         //到这里已经成功登录    
         cout << "ATM系统\n";
         cout << "0. 返回\n";
         cout << "1. 存款\n";
         cout << "2. 取款\n";
         cout << "3. 转账\n";
         cout << "4. 余额查询\n";
         cout << "5. 历史交易查询\n";
         cout << "6. 修改密码\n";
         cout << "7. 预测余额\n";
         cout << "请选择一个选项: ";
         bool flag = true;
         while (flag) {
             int option2;
             cin >> option2;
             switch (option2) {
             case 1: {   // 存款
                 double depositAmount;
                 cout << "请输入存款金额:";
                 cin >> depositAmount;
                 atm_manager.deposit(*currentAccount, depositAmount, key);  // 使用存款函数
                 break;
             }
             case 2: {   // 取款
                 double withdrawAmount;
                 cout << "请输入取款金额:";
                 cin >> withdrawAmount;
                 atm_manager.withdraw(*currentAccount, withdrawAmount, key);  // 使用取款函数
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
           cout << "系统已退出，感谢使用" << endl;
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




