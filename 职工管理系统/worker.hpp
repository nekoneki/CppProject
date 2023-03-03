/*
职工们的类。
包含一个职工抽象类父类
员工，经理，老板类为子类
*/
#pragma once
#include<string>
using namespace std;  

//职工抽象类:
class Worker
{
public:

    //Worker虚析构函数。 虚析构的用处是用来释放父类Worker们的子类的内存空间
    virtual ~Worker()
    {
        cout<<"调用了~Worker虚析构"<<endl;
    };
    //显示个人信息
    virtual void showInfo() = 0;

    //获取岗位名称
    virtual string getDeptName() = 0;

    //职工编号
    int m_Id;

    //职工姓名
    string m_Name;

    //部门编号
    int m_DeptId;


};
