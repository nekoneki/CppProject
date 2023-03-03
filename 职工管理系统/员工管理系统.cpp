#include<iostream>
using namespace std;
#include "employee.cpp"
#include "boss.cpp"
#include "manager.cpp"
#include"workerManager.cpp"





int main()
{
    workerManager wm;
   
    int select = 0;
    while (1)
    {
        wm.show_Menu();
        while(!(cin>>select))
        {
            system("clear");
            cout<<"请你不要输入字符!\n请选择正确数字! "<<endl;
            cin.clear(); // 清除cin的错误标记
            cin.ignore(128,'\n'); 
            wm.show_Menu();
        }        

        switch (select)
        {
        //退出程序
        case 0:
            wm.exitSystem();
            break;

        //增加职工
        case 1:
            wm.Add_Emp();
            break;

        //显示职工
        case 2:
            wm.Show_AllEmp();
            break;
        //删除职工
        case 3:
            wm.Delete_Emp();
            break;
        //修改职工信息
        case 4:
            wm.Modify_Emp();
            break;
        //查找职工信息
        case 5:
            wm.Show_An_Emp();
            break;

        //按照编号排序
        case 6:
            wm.Sort_Emp();
            break;
        //清空所有文档
        case 7:
            wm.Delete_All();
            break;

        default:
            system("clear");
            cout<<"请你输入正确选项!!\n"<<endl;
            break;
        }
        
    }
    
    
}