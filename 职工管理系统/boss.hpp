#pragma once
#include "worker.hpp"
#include<string>

//老板
class Boss: public Worker
{
public:

    //构造函数
    Boss(int id, string name, int deptID);

    ~Boss(){}

    //显示个人信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();




};
