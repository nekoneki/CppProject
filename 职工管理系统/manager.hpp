#pragma once
#include "worker.hpp"
#include<string>

//经理类
class Manager: public Worker
{
public:

    //构造函数
    Manager(int id, string name, int deptID);

    ~Manager(){}
    
    //显示个人信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();




};
