#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include "worker.hpp"
#define FILENAME "empFile.txt"

//管理类,用来管理系统的菜单,关闭菜单什么的..
class workerManager
{    
public:
    //构造与析构函数
    workerManager();
    ~workerManager();

    //菜单显示
    void show_Menu();

    //退出系统
    void exitSystem();

    //添加职工函数
    void Add_Emp();

    //把职工数组里的所有职工保存到txt文件中
    void save();

    //统计文件中已经存在的人数
    int get_EmpNumInFile();

    //初始化文件里已存在的员工:
    //将文件里已存在的员工全部重新写入到当前运行程序的员工数组中
    void init_Emp();

    //展示所有职工信息
    void Show_AllEmp();

    //展示指定员工信息
    void Show_An_Emp();

    //删除职工
    void Delete_Emp();

    //通过id判断职工是否存在 如果存在就返回该职工在数组中的位置
    //不存在则返回-1
    int isEmp_Exist(int id);

    //重载isEmp_Exist(string name)通过姓名判断员工是否存在
    //如果存在就返回该职工在数组中的位置 不存在返回-1
    int isEmp_Exist(string name);

    //修改职工信息
    void Modify_Emp();

    //按照职工编号排序:1.升序 2.降序
    void Sort_Emp();

    //清空文件，清空员工数组，清空一切并将必要参数全部初始化
    void Delete_All();

    //专门清空workerManager 的员工数组的指针内存以及这个数组的内存的函数
    void ClearMemoryArray();
    
    //数组里寻找是否与指定数字相同的数字
    //专门为第一次添加addEmp()时候判定是否有输入相同的id设计的函数
    int CheckID_First_Time(int *table,int size,int checkNumber);
    
    //判断文件是否为空 标志
    bool m_FileisEmpty;

    //记录职工人数
    int m_EmpNum;

    //职工数组的指针 这个数组里面存放的是Worker *类型的指针
    Worker ** m_EmpArray;

    

};



















