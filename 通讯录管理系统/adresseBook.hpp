#include<iostream>
#include<string>
#define MAX 10   //宏定义通讯录人数max
using namespace std;


struct person
{
    string m_name;
    int m_sex; //1:male  2:female
    int m_age;
    string m_Phone;
    string m_Addr;
};


struct AddressBooks
{ 
    //通讯录中人员列表
    person personArray[MAX];

    //通讯录中人员个数
    int m_size;  
};


//只允许输入1/2的函数判断
int Choose1_or_2()
{
    int select = 0;
    while((select<=0)||(select>2))
    {
        while(!(cin>>select))
        {
            cout<<"请你不要输入字符!\n请输入正确数字: ";
            cin.clear(); // 清除cin的错误标记
            cin.ignore(1024,'\n'); 
        }

        if((select<=0)||(select>2))
        {
            cout<<"请你输入数字1/2: ";
            cin.clear(); // 清除cin的错误标记
            cin.ignore(1024,'\n');
        }
        else cin.ignore(1024,'\n');  
    }
    return select;
}

//只允许输入1-5的函数判断
int Choose1_to_5()
{
    int select = 0;
    while((select<=0)||(select>5))
    {
        while(!(cin>>select))
        {
            cout<<"请你不要输入字符!\n请输入正确数字: ";
            cin.clear(); // 清除cin的错误标记
            cin.ignore(1024,'\n'); 
        }

        if((select<=0)||(select>5))
        {
            cout<<"请你输入数字1-5: ";
            cin.clear(); // 清除cin的错误标记
            cin.ignore(1024,'\n');
        }
        else cin.ignore(1024,'\n');  
    }
    return select;
}

//不允许输入小于等于零的数值函数判断
int ChooseNo0()
{
    int select = -1;
    while((select<=0))
    {
        while(!(cin>>select))
        {
            cout<<"请你不要输入字符!\n请输入正确数字: ";
            cin.clear(); // 清除cin的错误标记
            cin.ignore(1024,'\n'); 
        }

        if((select<=0))
        {
            cout<<"请你输入大于0的年龄: ";
            cin.clear(); // 清除cin的错误标记
            cin.ignore(1024,'\n');
        }
        else cin.ignore(1024,'\n');  
    }
    return select;
}

/*
单独显示一个人的信息 函数
*/
void showPerson(person per)
{
    cout<<per.m_name<<"\t\t"<<per.m_sex<<"\t\t"<<per.m_age<<"\t\t"<<per.m_Phone<<"\t\t"<<per.m_Addr<<endl;
}

/*
查找联系人子函数:按照姓名/电话查找
@method: string name/phone
@AddressBooks *adbks : 地址传参通讯录
@return wherePersonInAdbks: 返回找到的这个人在通讯录中的坐标位置
*/
int SubFunc_FindPerson_Method(string method,string findInfo, AddressBooks *adbks)
{
    int wherePerson= -1;
    for(int i = 0; i<adbks->m_size;++i)
    {
        if(method.compare("name") == 0)
        {
            if(findInfo.compare(adbks->personArray[i].m_name) == 0)
            {
                cout<<endl;
                wherePerson = i;
                showPerson(adbks->personArray[i]);
            }
        }
        else if(method.compare("phone") == 0)
        {
            if(findInfo.compare(adbks->personArray[i].m_Phone) == 0)
            {
                cout<<endl;
                wherePerson = i;
                showPerson(adbks->personArray[i]);
            } 
        }
    }
    return wherePerson;
}


/*
menu界面
@ AddressBooks *adbks 通讯录地址传参
*/
void menuShow()
{
    cout<<"欢迎来到通讯录主页。请输入您需要的选项:"<<endl;
    cout<<"1.添加联系人"<<endl;
    cout<<"2.显示在通讯录里的所有人信息"<<endl;
    cout<<"3.删除联系人"<<endl;
    cout<<"4.查找联系人"<<endl;
    cout<<"5.修改联系人"<<endl;
    cout<<"6.清空联系人"<<endl;
    cout<<"7.退出通讯录"<<endl;
}

/*
功能1 添加联系人
@ AddressBooks *adbks 通讯录地址传参
*/
void addPerson(AddressBooks *adbks)
{
    string name;
    int sex = 0;
    int age = -1;
    string Phone;
    string Addr;


    if (adbks->m_size == MAX) cout<<"通讯录人数已满!!"<<endl;
    
    else
    {
        cout<<"输入添加人姓名: ";
        cin>>name;
        
        cout<<"\n输入添加人性别 1:男 2:女: ";  
        sex = Choose1_or_2();

        cout<<"\n输入添加人年龄: "; 
        age = ChooseNo0();

        cout<<"\n输入添加人电话: ";
        cin>>Phone;
        
        cout<<"\n输入添加人地址: ";
        cin>>Addr;
        
        adbks->m_size += 1;
        adbks->personArray[adbks->m_size-1].m_name = name;
        adbks->personArray[adbks->m_size-1].m_sex = sex;
        adbks->personArray[adbks->m_size-1].m_age = age;
        adbks->personArray[adbks->m_size-1].m_Phone = Phone;
        adbks->personArray[adbks->m_size-1].m_Addr = Addr;
        system("clear");
        cout<<"添加成功！"<<endl;
        cin.ignore(1024,'\n');
    }
}

/*
功能2 显示所有通讯录的人信息
*/
void showAddresseBook(AddressBooks *adbks)
{
    system("clear");
    if(adbks->m_size==0) cout<<"通讯录为空！"<<endl;
    
    
    else if(adbks->m_size>0)
    {
        cout<<"通讯录人员列表如下:"<<endl;
        cout<<"姓名:\t\t"<<"性别:\t\t"<<"年龄:\t\t"<<"电话:\t\t"<<"住址:"<<endl;
        for(int i =0; i<adbks->m_size;++i) 
        {
            showPerson(adbks->personArray[i]);
        }
    }
   
}


/*
功能4 查找联系人
@return 1: 查到此人
@return -1: 没有此人
*/
int findPerson(AddressBooks *adbks)
{
    int select = 0;
    string name;
    string phone;
    int wherePersonInAdbks = -1;

    cout<<"请选择需要查找此人的方式 1:通过姓名 2:通过电话号码: ";
    select = Choose1_or_2();

    switch (select)
    {
    case 1:
        cout<<"输入需要查找的姓名: ";
        cin>>name;
        cout<<"查询结果为:";
        wherePersonInAdbks = SubFunc_FindPerson_Method("name",name,adbks);
        if(wherePersonInAdbks == -1) cout<<"查无此人."<<endl;
        break;
    
    case 2:
        cout<<"输入需要查找的电话号码: ";
        cin>>phone;
        wherePersonInAdbks = SubFunc_FindPerson_Method("phone",phone,adbks);
        if(wherePersonInAdbks == -1) cout<<"查无此人."<<endl;
        break;
    }
    return wherePersonInAdbks;
    
}

/*
功能4中客户选择性修改 1-5 姓名，性别，年龄，电话，地址 的Switch函数。防止冗余，特意建造此分函数。
*/
void AlterSwitchFunction(int choice, int i, AddressBooks *adbks)
{
    switch (choice)
    {
        case 1:
            cout<<"输入修改后的姓名: ";
            cin>>adbks->personArray[i].m_name;
            cout<<"修改成功!\n";
            break;
        
        case 2:
            cout<<"输入修改后的性别: ";
            adbks->personArray[i].m_sex = Choose1_or_2();
            cout<<"修改成功!\n";
            break;

        case 3:
            cout<<"输入修改后的年龄: ";
            adbks->personArray[i].m_age = ChooseNo0();
            cout<<"修改成功!\n";
            break;

        case 4:
            cout<<"输入修改后的联系电话: ";
            cin>>adbks->personArray[i].m_Phone;
            cout<<"修改成功!\n";
            break;

        case 5:
            cout<<"输入修改后的住址: ";
            cin>>adbks->personArray[i].m_Addr;
            cout<<"修改成功!\n";
            break;

        default:
            break;
    }
}

/*
功能5 修改联系人 通过电话/名字索引
*/
void AlterPerson(AddressBooks *adbks)
{
    int wherePerson = -1;
    int choice = 0;
    wherePerson = findPerson(adbks);

    if(wherePerson != -1)
    {
        cout<<"请输入要修改的信息 1.姓名 2.性别 3.年龄 4.联系电话 5.住址 "<<endl;
        choice = Choose1_to_5();
        AlterSwitchFunction(choice,wherePerson,adbks);
    }
}


/*
功能3 删除一个联系人
*/
void DeletePerson(AddressBooks *adbks)
{
    int wherePerson = -1;
    wherePerson = findPerson(adbks);
    string decide;
    
    if(wherePerson != -1)
    {
        cout<<"确认要删除此人??(y or n)"<<endl;
        cin>>decide;
        if (decide.compare("y") == 0)
        {
            if(wherePerson == MAX-1)
            {
                person per = {"",0,0,"",""};
                adbks->personArray[wherePerson] = per;
                adbks->m_size -=1;
                cout<<"删除完毕!"<<endl;
            }
            else
            {
                for(int i = wherePerson;i<MAX;i++)
                {
                    adbks->personArray[wherePerson] = adbks->personArray[wherePerson+1];
                }
                adbks->m_size -=1;
                cout<<"删除完毕!"<<endl;
            }
        }

        else if(decide.compare("n") == 0) cout<<"删除取消."<<endl;
        else cout<<"删除取消."<<endl;
        
    }
    
}

/*
功能6 清空联系人  包括m_size也清空
*/
void ClearAddresseBook(AddressBooks *adbks)
{
    person per = {"",0,0,"",""};
    for (int i = 0; i <MAX; ++i)
    {
        per.m_name = adbks->personArray[i].m_name;
        per.m_age = adbks->personArray[i].m_age;
        per.m_sex = adbks->personArray[i].m_sex;
        per.m_Phone = adbks->personArray[i].m_Phone;        
        per.m_Addr = adbks->personArray[i].m_Addr;
    }
    adbks->m_size = 0;
    cout<<"clear finish!"<<endl;
}
