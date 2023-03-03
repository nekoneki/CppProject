/*
通讯录管理系统。（不使用文件txt管理，即时的通讯录）
实现以下功能：
1. 添加联系人 （姓名，性别，年龄，联系电话，家庭住址） 最多可以添加5人
2. 显示所有联系人以及其信息
3. 删除联系人
4. 查找联系人 通过电话/姓名
5. 修改联系人：通过电话/姓名查找联系人然后选择修改其信息。
6. 清空联系人
7. 退出通讯录
*/

#include <iostream>
#include <string>
#include"adresseBook.hpp"
using namespace std;

int main()
{
    
    AddressBooks adbs;
    person pers;
    adbs.m_size = 0;
    char select;
    while (1)
    {
        menuShow();
        cin>>select;
        switch (select)
        {
        /*
        功能1.添加联系人
        */
        case '1':
            addPerson(&adbs);  
            break;

        case '2':
            showAddresseBook(&adbs);

            break;

        case '3':
            DeletePerson(&adbs);
            break;

        case '4':
            findPerson(&adbs);
            break;

        case '5':
            AlterPerson(&adbs);
            break;

        case '6':
            ClearAddresseBook(&adbs);
            break;

        case '7':
            system("clear");
            cout<<"再见！"<<endl;
            return 0;
            break;
        
        default:
            system("clear");
            cin.clear();
            cin.ignore(1024,'\n');
            cout<<"请输入正确数字!!\n"<<endl;
            break;
        }
        
        
    }
    
    
}
