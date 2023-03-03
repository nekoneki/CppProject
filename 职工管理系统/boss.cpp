#pragma once
#include<iostream>
#include "boss.hpp"
using namespace std;  


Boss::Boss(int id, string name, int deptID)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = deptID;
}

//显示个人信息
void Boss::showInfo()
{
    cout<<"编号: "<<this->m_Id
        <<"\t姓名: "<<this->m_Name
        <<"\t岗位: "<<this->getDeptName()
        <<"\t职责: 管理公司所有事务"<<endl;
}

//获取岗位名称
string Boss::getDeptName()
{
    return string("老板");
}



