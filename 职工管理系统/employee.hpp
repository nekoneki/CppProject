#pragma once
#include "worker.hpp"
#include<string>

//员工类
class Employee: public Worker
{
public:
    //默认构造函数
    Employee(){};
    //构造函数
    Employee(int id, string name, int deptID);

    ~Employee(){}
    //显示个人信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();

};
