#pragma once
#include<iostream>
#include "manager.hpp"
using namespace std;  


Manager::Manager(int id, string name, int deptID)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = deptID;
}

//显示个人信息
void Manager::showInfo()
{
    cout<<"编号: "<<this->m_Id
        <<"\t姓名: "<<this->m_Name
        <<"\t岗位: "<<this->getDeptName()
        <<"\t职责: 完成老板交给的任务 并且下发任务给员工"<<endl;
}

//获取岗位名称
string Manager::getDeptName()
{
    return string("经理");
}



