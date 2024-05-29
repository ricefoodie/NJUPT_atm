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
     cout << "ATMϵͳ\n";
     cout << "0. �˳�\n";
     cout << "1. ����Ա\n";
     cout << "2. �û�\n";
     cout << "��ѡ��һ��ѡ��: ";
     int option=-1;
     while (option < 0 || option>2) {
         cin >> option;
         if (option < 0 || option>2) {
             cout << "����������" << endl;
         }
     }
     int managepassword = 123456, inputpassword;
     switch (option) {
     case 1:
         cout << "���������Ա���룺" ;
         cin >> inputpassword;
         while (inputpassword != managepassword) {
             cout << "����������,������0�ص���ҳ��"<<endl;
             cin >> inputpassword;
             if (inputpassword == 0){
                 goto StartMenu;
             }
             
         }
         cout <<endl<< "����Ա��¼�ɹ�\n1.�û���Ϣ" << endl;
         cout << "2.�����û�" << endl;
         cout << "3.�������ڴ���˻�" << endl;
         cout << "0.����" << endl;
         while (flag2) {
         int option3;
         cin >> option3;
         switch (option3) {
         case 1: { 
             FileHandler::printAllAccountInfo();
             cout << "\n\n1.�����ض��û�" << endl;
             cout << "2.�����û�״̬" << endl;
             cout << "0.����" << endl;
             int option4;
             int key = 5;
             string id;
             cin >> option4;
             switch (option4) {
             case 1:
                 cout << "\n������Ҫ�������û�ID" << endl;
                 cin >> id;
                 atm_manager.queryTransactionHistory(id, key);
                 break;
             case 2:
                 cout << "\n�û�ID" << endl;
                 cin >> id;
                 FileHandler::updateAccountState(id, 1, key);
                 cout << "�ѽ���" << endl;
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
         int loginAttempts = 0;//��¼���������
         string id;
         int key;
         Account* currentAccount;
         
         do {
             cout << "��������ȷ�Ŀ���,������0�ص���ҳ��:";
             cin >> id;
             if (id == "0") {
                 goto StartMenu;
             }
             key = generateKey(id);            
             currentAccount = FileHandler::retrieveAccountById(id, key);

         } while (currentAccount == nullptr);
         if (FileHandler::getAccountState(id,key) == 0) {
             cout << "����������ϵ����Ա�����" << endl;
             break;
         }
             
         while (!(atm_manager.verifyLogin(id))) {//�ȵ�¼
             loginAttempts++;

             if (loginAttempts < 3) {
                 cout << "��������������Ѿ������ " << loginAttempts << " �Σ���ʣ" << 3 - loginAttempts << "�λ��ᣡ" << endl;
             }
             else {
                 cout << "������" << endl;
                 FileHandler::updateAccountState(id,0,key);
                 return 1; // �˳�����
             }
         }
         //�������Ѿ��ɹ���¼  
         FileHandler::updateAccountState(id, FileHandler::getAccountState(id, key)+1, key);
         if (FileHandler::getAccountState(id, key) >= 5)
         {
             cout << "�˻���ȫ��飺��⵽���Ѿ���ε�¼û���޸����룬�����޸�����\n\n";
             Sleep(2500);
         }
         cout << "ATMϵͳ\n";
         cout << "0. ����\n";
         cout << "1. ���\n";
         cout << "2. ȡ��\n";
         cout << "3. ת��\n";
         cout << "4. ����ѯ\n";
         cout << "5. ��ʷ���ײ�ѯ\n";
         cout << "6. �޸�����\n";
         cout << "7. Ԥ�����\n";
      //   cout << "8. �������ڴ���˻�\n";
         cout << "8. ���Ҷһ�" << endl;
         bool flag = true;
         while (flag) {
             cout << "��ѡ��һ��ѡ��: ";
             int option2;
             char yn;
             cin >> option2;
             switch (option2) {
             case 1: {   // ���
                 double depositAmount;
                 cout << "����������:";
                 cin >> depositAmount;
                 atm_manager.deposit(*currentAccount, depositAmount, key);  // ʹ�ô���
                 cout << "�Ƿ��ӡ�ص���y/n" << endl;
                 cin >> yn;
                 if (yn == 'y')
                     cout << "��ӡ�ɹ���";
                 break;
             }
             case 2: {   // ȡ��
                 double withdrawAmount;
                 cout << "������ȡ����:";
                 cin >> withdrawAmount;
                 atm_manager.withdraw(*currentAccount, withdrawAmount, key);  // ʹ��ȡ���
                 cout << "�Ƿ��ӡ�ص���y/n" << endl;
                 cin >> yn;
                 if (yn == 'y')
                     cout << "��ӡ�ɹ���";
                 break;
             }
             case 3: {
                 string  toAccountId;
                 double amount;
                 cout << "�������տ�˺�: ";
                 cin >> toAccountId;
                 cout << "������ת�˽��: ";
                 cin >> amount;

                 // ִ��ת��
                 bool success = atm_manager.transfer(id, toAccountId, amount);
                 if (success) {
                     cout << "ת�˳ɹ���\n";
                     cout << "�Ƿ��ӡ�ص���y/n" << endl;
                     cin >> yn;
                     if (yn == 'y')
                         cout << "��ӡ�ɹ���";
                 }
                 else {
                     cout << "ת��ʧ�ܡ�\n";
                 }
             }
             case 4: {//����ѯ
                 atm_manager.queryBalance(id, key);
                 break;
             }
             case 5: {//��ѯ������ʷ��¼
                 atm_manager.queryTransactionHistory(id, key);
                 break;
             }
             case 6: {//�޸�����
                 atm_manager.changePassword(id, key);
                 break;
             }
             case 7: {
             atm_manager.predictBal(id,key, currentAccount->getBalance());
             break;
             }
             case 8: {
             cout<<"��������Ҫ�һ��Ļ������ࣺ��ֱ�Ӵ浽�˻���"<<endl;
             cout << "1.��Ԫ->����ң�2.Ӣ��->����ң�3.ŷԪ->�����" << endl;
             int cointype;
             cin >> cointype;
             double depositAmount;
             cout << "������һ����:";
             cin >> depositAmount;
             
             switch (cointype) {
             case 1:depositAmount *= 7.24;    break;
             case 2:depositAmount *= 9.03;    break;
             case 3:depositAmount *= 7.73;    break;
             default:cout << "�����������������롣" << endl; break;
             }
             atm_manager.deposit(*currentAccount, depositAmount, key);  // ʹ�ô���
             cout << "�Ƿ��ӡ�ص���y/n" << endl;
             cin >> yn;
             if (yn == 'y')
                 cout << "��ӡ�ɹ���";
             break;
             }
             case 0: {//����
                 flag = false;
                 cout<< "���سɹ�,����������ѡ��" << endl;
                 
                 break;
             }
             default: {
                 cout << "������������������" << endl;
                 break;
             }
             }
         }break;
     }
     case 0: {
           cout << "ϵͳ���˳����뱣����������п�" << endl;
           exit(0);
           break;}
     default: {
         cout << "������������������" << endl;
         break;
     }
    }
}
    return 0;
}




