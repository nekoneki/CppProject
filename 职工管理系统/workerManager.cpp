#include "workerManager.hpp"
#include "employee.hpp"
#include "boss.hpp"
#include "manager.hpp"

workerManager::workerManager()
{
    //情况1:如果文件不存在的话:
    ifstream ifs;
    ifs.open(FILENAME, ios::in |ios::binary);
    if(!ifs.is_open())
    {
        //cout<<"文件不存在!!!"<<endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileisEmpty = true;
        ifs.close();
        return;
    }

    //情况2:如果文件存在但是数据为空
    char ch;
    ifs>>ch;
    //空文件里面只有一个eof标志。只要读取一个字符就能读取到的 
    if(ifs.eof())
    {
        //cout<<"文件为空!!!"<<endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileisEmpty = true;
        ifs.close();
        return;
    }

    //当情况1/2发生后,以下的情况3代码绝对不会运行。因为情况1/2里有return
    //意思是直接结束了workerManager()的构造函数。
    //反之如果文件存在,那么必定 只运行情况3的代码。
   
    //情况3:如果文件存在并且里面有员工记录
    int num = this->get_EmpNumInFile();
    this->m_EmpNum = num;

    //开辟空间
    this->m_EmpArray = new Worker*[this->m_EmpNum];

    //将文件中的数据存放到职工数组中
    this->init_Emp();
    this->m_FileisEmpty = false;
}

//workerManager的析构函数,在关闭程序之前彻底释放干净内存
//先释放掉指针数组中储存着的每一个指针内存，再释放掉整个指针数组
workerManager::~workerManager()
{
    this->ClearMemoryArray();
    
}

//显示菜单
void workerManager::show_Menu()
{
    cout<<"欢迎使用职工管理系统。请输入您需要的选项:"<<endl;
    cout<<"0.退出管理程序"<<endl;
    cout<<"1.增加职工信息"<<endl;
    cout<<"2.显示职工信息"<<endl;
    cout<<"3.删除离职员工"<<endl;
    cout<<"4.修改职工信息"<<endl;
    cout<<"5.查找职工信息"<<endl;
    cout<<"6.按照编号排序"<<endl;
    cout<<"7.清空所有文档"<<endl;
    cout<<endl;
}

//退出程序
void workerManager::exitSystem()
{
    //system("clear");
    cout<<"再见！"<<endl;
    exit(0);
}

//数组里寻找是否与指定数字相同的数字
//专门为第一次添加addEmp()时候判定是否有输入相同的id设计的函数
//0：代表不存在 1：代表存在了
int workerManager::CheckID_First_Time(int *table,int size,int checkNumber)
{
    int ret = 0;
    for (int j = 0; j < size; j++)
    {
        if(table[j]==checkNumber) return 1;
    }
    return ret;
}

//添加职工
void workerManager::Add_Emp()
{
    int *table = NULL; //用来判断首次Add_Emp时候用户是否输入相同的id
    int addNum = 0;
    cout<<"请输入添加的员工数量"<<endl;
    cin>>addNum;

    if(addNum>0)
    {
        table = new int[addNum];
        //计算添加空间大小:新空间人数 = 原来记录人数+新增人数
        int newSize = this->m_EmpNum + addNum;
        
        //开辟新空间
       /* 因为可以用多态来将不同类型的职工放到同一个数组里:父类指针指向子类对象的方法
        所以我们可以开一个存放父类指针的数组
        解释: 本来，int *p = &a; *p是个存放int变量/存着一堆int变量的数组 地址的指针
        那么int * (*poi) = &p; (*poi)就是一个存放着int *类型指针/存着一堆int* 类型指针的数组 地址的指针
        */
        
        Worker * (*newSpace) = new Worker *[newSize];
        

        //如果原来数组里有数据, 则将原来空间下的数据拷贝到新的空间下面
        if(this->m_EmpArray!=NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //新的数据批量添加
        for (int i = 0; i < addNum; i++)
        {
            int id; //职工编号
            string name; //职工姓名
            int dSelect; //职工部门选择
            
            cout<<"请输入第"<<i+1<<"位新职工编号:"<<endl;
            cin>>id;

            if(!m_FileisEmpty)
            {
                while(isEmp_Exist(id)!=-1)
                {
                    cout<<"您输入的编号已存在,请重新输入编号"<<endl;
                    cin>>id;
                }
            }
            
            else
            {
                if(i==0)    table[i] = id;
                else if(i>0)
                {
                    cout<<"进入"<<endl;
                    while(this->CheckID_First_Time(table,i,id)==1)
                    {
                        cout<<"您输入的编号已存在,请重新输入编号"<<endl;
                        cin>>id;
                    }
                    table[i] = id;
                }
            }
            
            cout<<"请输入第"<<i+1<<"位新职工姓名:"<<endl;
            cin>>name;

            cout<<"请选择该职工的岗位:"<<endl;
            cout<<"1.普通职工"<<endl;
            cout<<"2.经理"<<endl;
            cout<<"3.老板"<<endl;
            cin>>dSelect;

            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id,name,1);
                break;
            case 2:
                worker = new Manager(id,name,2);
                break;
            case 3:
                worker = new Boss(id,name,3);
                break;
            default:
                break;
            }

            //将创建了的职工保存到新的职工数组newSpace中(保存到最新的位置那)
            newSpace[this->m_EmpNum +i] = worker;
        }

        //把原来数组里的所有职工都迁移到了新的空间newSpace后, 应该把原来的指针数组的内存释放
        delete[] this->m_EmpArray;

        //把职工数组的指针指向新数组
        this->m_EmpArray = newSpace;

        //更新职工的总人数
        this->m_EmpNum = newSize;

        //更新 文件里不为空的标志为false
        this->m_FileisEmpty = false;

        //提示成功添加:
        system("clear");
        cout<<"成功添加"<<addNum<<"名新职工"<<endl;
        this->save();
        delete table;
        //将新数组里的所有职工信息写入文件后,不能去释放这个newSpace!!这个新开辟的内存空间
        //员工数组指针就已经指向他了！！万万不可释放!!

    }
    else
    {
        cout<<"输入有误。请输入大于0的数字"<<endl;
    }
}

//将添加的职工保存在文件中
void workerManager::save()
{
    //output to file 以写的方式打开文件 + 二进制写入
    //如果不加ios::app, ios::out默认是会先清除文件内容再往里面写入的
    ofstream ofs(FILENAME,ios::out | ios::binary);

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        //m_EmpArray[i]里存的是Worker*指针。如果要使用write函数,要把这个指针强转成const char*
        ofs.write((const char *)this->m_EmpArray[i],sizeof(Worker));
    }
    ofs.close();

} 

//每次重新启动程序时,如果员工文件存在并且里面不为空,则计算员工文件里已经存了多少员工
//返回已经存储了的员工数量
//count-1的原因是我这样子写,每次总会从文件里读取出来一个名字为空,id为0的人..所以总数-1
int workerManager::get_EmpNumInFile()
{
    short initial_num = 1000;
    short count = 0;
    
    //建立一个Employee数组来保存从文件中读取来的每一个员工详细信息(包括id,姓名..)
    Employee * empExist = new Employee[initial_num];
    ifstream ifs(FILENAME,ios::in | ios::binary);
    for(int i=0;i<initial_num;i++)
    {
        //如果读取到了eof则立即返回获取的人数-1
        if(ifs.eof()) 
        {
            return count-1;
        }
    
        else
        {
            //read from file.从文件里读取出来的数据是一个个员工的真实数据
            //empExist[i]代表第i个员工. &empExist[i]代表第i个员工的地址。
            //我们要把这个地址强转成char* 才能用read函数
            ifs.read((char*)&empExist[i],sizeof(Employee));
            count++;
        }
       
    }
    return count-1;

}

//每次重新启动程序时,如果员工文件存在,从此文件里提取出所有的员工信息
//并放进现在运行时的EmpArray里
void workerManager::init_Emp()
{
    //临时的职工数组，用于储存从文件里提取出来的职工
    Employee * empExist = new Employee[this->m_EmpNum];

    //input from file
    ifstream ifs(FILENAME,ios::in | ios::binary);

    for(int i=0;i<this->m_EmpNum;i++)
    {
        Worker *worker = NULL;
        //EmpExist[i]指的是empExist[]数组里的第i名员工,加个&是取址符
        ifs.read((char*)&empExist[i],sizeof(Employee));

        //这里对提取出来的员工进行分类。比如如果提取出来的empExist[i]是普通职工,
        //则新建一个普通职工对象放他，并且最后将他放到当前运行的程序的职工数组中
        if(empExist[i].m_DeptId == 1)
        {
            worker = new Employee(empExist[i].m_Id,empExist[i].m_Name,empExist[i].m_DeptId);
        }

        else if(empExist[i].m_DeptId == 2)
        {
            worker = new Manager(empExist[i].m_Id,empExist[i].m_Name,empExist[i].m_DeptId);
        }

        else if(empExist[i].m_DeptId == 3)
        {
            worker = new Boss(empExist[i].m_Id,empExist[i].m_Name,empExist[i].m_DeptId);
        }
        //将empExist[i]放到当前运行的程序的职工数组中
        this->m_EmpArray[i] = worker;
    }
    //关闭文件。
    ifs.close();


}

//多态显示所有职工信息
void workerManager::Show_AllEmp()
{
    //判断职工文件是否为空
    if(this->m_FileisEmpty)
    {
        cout<<"文件不存在或者为空!!"<<endl;
    }

    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo();
        }
    }
}


//通过id判断员工是否存在于当前运行程序的职工数组中。存在则返回其数组中的index 
//不存在则返回-1
int workerManager::isEmp_Exist(int id)

{
    int index = -1;

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

//重载isEmp_Exist 通过姓名判断员工是否存在于当前运行程序的职工数组中。
//存在则返回index不存在返回-1
int workerManager::isEmp_Exist(string name)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Name == name)
        {
            index = i;
            break;
        }
    }
    return index;
}


//删除一个员工 通过编号删除
void workerManager::Delete_Emp()
{
    //先判断文件是否存在
    if(this->m_FileisEmpty)
    {
        cout<<"文件不存在或者记录为空!!"<<endl;
    }

    else
    {
        cout<<"请输入您想要删除的职工编号"<<endl;
        int id = 0;
        cin>>id;

        //判断员工是否存在于当前运行程序的职工数组中。
        int index = this->isEmp_Exist(id);

        //如果该员工在数组中:
        if(index != -1)
        {
            //从此要删除的员工的位置开始,到总人数-1的地方为止,把后面的员工信息填补到前一位上,以此类推
            for (int i = index; i < this->m_EmpNum-1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            //更新数组中的人数
            this->m_EmpNum -=1 ;
            
            //同步更新到文件中
            this->save();
            cout<<"删除成功!!"<<endl;

            //删除员工并不需要释放m_EmpArray[index]和m_EmpArray[m_EmpNum]的内存。任何的释放都会导致内存报错
            //不信你试试
           
        }
        else cout<<"未找到该员工!!"<<endl;
    }
}


//修改职工信息
void workerManager::Modify_Emp()
{
    //先判断文件是否存在
    if(this->m_FileisEmpty)
    {
        cout<<"文件不存在或者记录为空!!"<<endl;
    }
    else
    {
        cout<<"请输入您想要修改的职工编号"<<endl;
        int id = 0;
        cin>>id;

        //判断员工是否存在于员工数组中
        int index = this->isEmp_Exist(id);

        //如果存在
        if(index != -1)
        {
            //释放这个index上旧的员工信息内存。因为我们等下要让这个index的指针指向新创建的员工对象(即修改信息后的员工)
            delete this->m_EmpArray[index];

            int idChange = 0;
            string nameChange = "";
            int deptChange = 0;
            cout<<"查到此人:"<<endl;
            cout<<"请输入新的id:"<<"(此人原id为:"<<this->m_EmpArray[index]->m_Id<<")"<<endl;
            cin>>idChange;

            //防止同号。
            while(isEmp_Exist(idChange)!=-1)
            {
                cout<<"您输入的编号已存在,请重新输入编号"<<endl;
                cin>>idChange;
            }

            this->m_EmpArray[index]->m_Id = idChange;

            cout<<"请输入新的名字:"<<"(此人原名为:"<<this->m_EmpArray[index]->m_Name<<")"<<endl;
            cin>>nameChange;
            this->m_EmpArray[index]->m_Name = nameChange;

            cout<<"请输入新的部门编号:"<<"(此人原部门编号为:"<<this->m_EmpArray[index]->m_DeptId<<")"<<endl;
            cout<<"1.普通职工\n2.经理\n3.老板"<<endl;
            cin>>deptChange;
            this->m_EmpArray[index]->m_Id = deptChange;

            //这个worker不能释放!!!!这是我们为了修改后的员工开辟的新内存,
            //储存着这个员工修改后的信息并且让这个员工本来的指针指向了这个内存,
            //要直到功能7被按下/程序彻底结束才可释放!!!
            Worker *worker = NULL;
            switch (deptChange)
            {
            case 1:
                worker = new Employee(idChange,nameChange,deptChange);
                break;

            case 2:
                worker = new Manager(idChange,nameChange,deptChange);
                break;
            case 3:
                worker = new Boss(idChange,nameChange,deptChange);
                break;
            
            default:
                break;
            }
            
            //将此新地址的职工指针更新到职工数组中
            this->m_EmpArray[index] = worker;
            cout<<"修改成功!!!"<<endl;

            //将更新后的职工数组重新写入到文件。
            this->save();


           
            
        }
        else cout<<"未找到该员工，修改失败!"<<endl;
    }
}

//显示一个指定员工信息
void workerManager::Show_An_Emp()
{
    //先判断文件是否存在
    if(this->m_FileisEmpty)
    {
        cout<<"文件不存在或者记录为空!!"<<endl;
    }
    else
    {
        int choice = 0;
        cout<<"请选择您想要查找员工的方式:\n1.通过姓名\n2.通过员工编号"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            {
                cout<<"请输入您想要查找的职工姓名"<<endl;
                string name = "";
                cin>>name;
                int index = this->isEmp_Exist(name);
                if(index != -1)
                {
                    system("clear");
                    cout<<"查到此人:"<<endl;
                    //调用showInfo()多态显示员工信息
                    this->m_EmpArray[index]->showInfo();
                }
                else cout<<"未找到该员工!!"<<endl;
            }
            break;

        case 2:
            {
                cout<<"请输入您想要查找的职工编号"<<endl;
                int id = 0;
                cin>>id;
                int index = this->isEmp_Exist(id);
                if(index != -1)
                {
                    system("clear");
                    cout<<"查到此人:"<<endl;
                    this->m_EmpArray[index]->showInfo();
                }
                else cout<<"未找到该员工!!"<<endl;
            }
            break;
        
        default:
            break;
        }
       
    }
}

//给员工排序通过编号升序/降序排序
void workerManager::Sort_Emp()
{
    //先判断文件是否存在
    if(this->m_FileisEmpty)
    {
        cout<<"文件不存在或者记录为空!!"<<endl;
    }
    else
    {
        int choice;
        cout<<"请问需要以员工id升序排序还是降序排序?\n1.升序\n2.降序"<<endl;
        cin>>choice;
        /*冒泡排序算法
        if(choice==1)
        {

            for (int i = 0; i < this->m_EmpNum-1; i++)
            {
                for (int j = 0; j<m_EmpNum-i-1; j++)
                {
                    if(this->m_EmpArray[j]->m_Id > this->m_EmpArray[j+1]->m_Id)
                    {
                        Worker * workerTemp;
                        workerTemp =this->m_EmpArray[j];
                        this->m_EmpArray[j] = this->m_EmpArray[j+1];
                        this->m_EmpArray[j+1] = workerTemp;
                    }
                }
            }
            this->save();
        
        }
        else if(choice ==2)
        {
            for (int i = 0; i < this->m_EmpNum-1; i++)
            {
                for (int j = 0; j<m_EmpNum-i-1; j++)
                {
                    if(this->m_EmpArray[j]->m_Id < this->m_EmpArray[j+1]->m_Id)
                    {
                        Worker * workerTemp;
                        workerTemp =this->m_EmpArray[j];
                        this->m_EmpArray[j]= this->m_EmpArray[j+1];
                        this->m_EmpArray[j+1] = workerTemp;
                    }
                }
            }
            this->save();
            
        }
        */
        
        //选择排序算法:
        for (int i = 0; i < this->m_EmpNum-1; i++)
        {
            int minOrMaxIndex = 0;

            //如果是升序 min index， 把找到的小的往最左边排
            if (choice==1)
            {
                minOrMaxIndex = i;
                for (int j = i+1; j<this->m_EmpNum; j++)
                {
                    // 54321
                    if(this->m_EmpArray[j]->m_Id < this->m_EmpArray[minOrMaxIndex]->m_Id)
                        minOrMaxIndex = j;
                }
                
            }
            
            //如果是降序 要使用max index， 把找到的大的往最左边排
            else if(choice ==2)
            {
                minOrMaxIndex = i;
                for (int j = i+1; j < this->m_EmpNum; j++)
                {
                    if(this->m_EmpArray[j]->m_Id > this->m_EmpArray[minOrMaxIndex]->m_Id)
                    {
                        minOrMaxIndex = j;
                    }
                }
                
                
            }

            if(minOrMaxIndex != i)
            {
                Worker *work;
                work = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMaxIndex];
                this->m_EmpArray[minOrMaxIndex] = work;
                this->save();
                
            }

        }
        system("clear");
        cout<<"排列完毕!"<<endl;
        this->Show_AllEmp();
        
    }
}

//专门清空workerManager 的员工数组的指针内存以及这个数组的内存的函数
void workerManager::ClearMemoryArray()
{
    if(this->m_EmpArray!=NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if(this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
        }
        delete[] m_EmpArray;
        this->m_EmpArray = NULL;
        this->m_FileisEmpty = 1;
        this->m_EmpNum = 0;
    }
}
//清空文件，清空员工数组，清空一切
void workerManager::Delete_All()
{
    //先判断文件是否存在
    if(this->m_FileisEmpty)
    {
        cout<<"文件不存在或者记录为空!!"<<endl;
    }

    else
    {
        int final_Choice = -1;
        cout<<"您真的要彻底删除所有员工信息吗???(1.yes \t 2.no)"<<endl;
        cin>>final_Choice;
        if (final_Choice ==1)
        {
            //删除原来存在的文件后，重新创建一个新文件 相当于清空文件
            ofstream ofs(FILENAME,ios::trunc|ios::binary);
            ofs.close();
            //彻底清空一切内存
            //(虽然workerManager析构函数里也写了这些清空内存的代码,但是并不是只有在程序结束的时候我们才要清空呀,
            //在程序运行的时候我们也有要清空内存的需求)
            this->ClearMemoryArray();
            
            system("clear"); 
            cout<<"清空成功!!!"<<endl;

        }

        else if(final_Choice ==2)
        {
            system("clear");
            cout<<"用户取消清空文件操作。返回主菜单。"<<endl;
            return;
        }
    } 
}

    