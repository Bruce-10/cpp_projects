
#include "EmployeeManagement.h"
#include "employees.h"
#include "manger.h"
#include "boss.h"
#include "workers.h"

EmployeeManagement::EmployeeManagement()
{
	//1.文件不存在
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open()) //文件不存在
	{
		mFilsIsEmpty = true;
		mEmpArry = NULL;
		mENum = 0;
		ifs.close();

		cout << "文件不存在\t";
		return;
	}
	//2.文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		mFilsIsEmpty = true;
		mEmpArry = NULL;
		mENum = 0;
		ifs.close();
		cout << "文件存在,但为空\t";
		return;
	}
	//3.文件存在且不为空
	//else
	//{
	//	//fileFrom();
	//	mFilsIsEmpty = false;
	//	mENum = get_mENum();
	//	ifs.close();
	//	cout << "文件存在,不为空\n";
	//	return;
	//}
	//else
	//{
	//	//mFilsIsEmpty = false;
	//	////mEmpArry = NULL;
	//	//mENum = get_mENum();
	//	//ifs.close();
	//	//cout << "文件存在,不为空\n";
	//	//return;
	//}
	get_mENum();
	//fileFrom();
	mEmpArry = new Workers *[mENum];
	fileFrom();
	show();
}
EmployeeManagement::~EmployeeManagement()
{
	eFree();
	
}
void EmployeeManagement::eFree()
{
	if (mEmpArry != NULL)
	{
		for (int i = 0; i < mENum; i++)
		{
			if (mEmpArry[i] != NULL)
			{
				delete mEmpArry[i];
				mEmpArry[i] = NULL;
			}
		}
		mFilsIsEmpty = true;
		mENum = 0;
		delete[] mEmpArry;
		mEmpArry = NULL;
	}
}
void EmployeeManagement::menu()
{
	cout << "--------------------------------------------\n";
	cout << "1.增\t2.删\n";
	cout << "3.查\t4.改\n";
	cout << "5.显示\t6.按照标号排序\n";
	cout << "7.清空\t0.退出\n";
	cout << "--------------------------------------------\n";
}
void EmployeeManagement::mExit()
{
	cout << "欢迎下次使用\n";
	system("pause");
	exit(0);
}
void EmployeeManagement::add()
{
	mENum++;
	//Workers** mEmpArry;
		//mEmpArry = new Workers *[mENum];
	Workers** newArry = new Workers * [mENum];
	if (mEmpArry != NULL) {  //数组阔容
		for (int i = 0; i < mENum; i++)
		{
			newArry[i] = mEmpArry[i];
		}
	}
	int num = 0;
	string name;
	cout << "输入编号：";
	cin >> num;
	cout << "输入名字：";
	cin >> name;

	cout << "请输入级别：\n"
		"1.普通员工  2.经理  3.老板 \n";
	int level = 0;
	cin >> level;
	Workers* w = NULL;
	switch (level)
	{
	case 1:  //员工    
		//Employees::Employees(int num, string name, int level)
		w = new  Employees(num, name, level);
		break;
	case 2:  //经理
		w = new  Manger(num, name, level);
		break;
	case 3:  //老板
		w = new  Boss(num, name, level);
		break;
	default:
		cout << "输错了\n";
		return;
	}
	newArry[mENum - 1] = w;
	delete[] mEmpArry;
	mEmpArry = newArry;
	//delete[] newArry;    //程序终止
	cout << "添加成功\n";
	save(); //保存数据至文件
	mFilsIsEmpty = false;
	system("pause");
	system("cls");

}
void EmployeeManagement::show()
{
	for (int i = 0; i < mENum; i++)
	{
	
		cout << "编号\t姓名\t级别\n";
		cout << mEmpArry[i]->mNum<< "\t" << mEmpArry[i]->mName << "\t" << mEmpArry[i]->mLevel << endl;

	}
	//save(); //保存数据至文件
	//mFilsIsEmpty = false;

	//cout << mENum<<endl;

}
void EmployeeManagement::save()
{
	ofstream ofs;
	ofs.open (FILENAME, ios::out);
	for (int i = 0; i < mENum; i++)
	{
		/*ofs << "  " << "编号\t" << "姓名\t" << "级别\n"
			<<i<<'.' */
			ofs<< mEmpArry[i]->mNum << "\t"
			<< mEmpArry[i]->mName << "\t" 
			<< mEmpArry[i]->mLevel << endl;
	}
	ofs.close();
}
//文件数据输入到内存
int EmployeeManagement::get_mENum()
{
	ifstream ifs;
	//ios::in：文件以输入方式打开（文件数据输入到内存）
	ifs.open (FILENAME, ios::in);
	int num;
	string name;
	int levle;
	int cont = 0;
	while (ifs >> num && ifs >> name && ifs >> levle)
	{
		cont++;
	}
	ifs.close();
	mENum = cont;
	cout << "get_mENum数据数：" << cont << endl;
	return cont;
}
int EmployeeManagement::fileFrom()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int num;
	string name;
	int level;
	int index = 0;
	while (ifs >> num && ifs >> name && ifs >> level)
	{
		Workers* w = NULL;
		switch (level)
		{
		case 1:  //员工    
			//Employees::Employees(int num, string name, int level)
			w = new  Employees(num, name, level);
			break;
		case 2:  //经理
			w = new  Manger(num, name, level);
			break;
		case 3:  //老板
			w = new  Boss(num, name, level);
			break;
		}
		//mEmpArry = new Workers * [mENum];
		mEmpArry[index] = w;
		index++;
	}
	mENum = index;
	cout << "fileFrom数据数：" << index << endl;
	return index;
}

void EmployeeManagement::showEmp()
{
	if (mFilsIsEmpty)
	{
		cout << "文件为空或不存在\n";
	}
	else
	{
		for (int i = 0; i < mENum; i++)
		{
			mEmpArry[i]->showInfor();
		}
		cout << "员工总数：" << mENum << endl;
	}
}
void EmployeeManagement::mDelEmp()
{
	if (mFilsIsEmpty)
	{
		cout << "文件为空或不存在\n";
		//system("pause");
		return;
	}
	int id = 0;
	cout << "请输入要删除的员工编号：";
	cin >> id;
	int ret = isExist(id);
	if (ret >= 0) //如果存在
	{
		mEmpArry[ret]->mNum = mEmpArry[mENum - 1]->mNum;
		mEmpArry[ret]->mName = mEmpArry[mENum - 1]->mName;
		mEmpArry[ret]->mLevel = mEmpArry[mENum - 1]->mLevel;
		mENum--;
		save();
	}
	else {
		cout << "不存在\n";
	}
	system("pause");
	system("cls");

}
int EmployeeManagement::isExist(int id)
{
	for (int i = 0; i < mENum; i++)
	{
		if (mEmpArry[i]->mNum == id)
		{
			return i;
		}
	}
	return -1;
}
void EmployeeManagement::mChange()
{
	if (mFilsIsEmpty)
	{
		cout << "文件为空或不存在\n";
		return;
	}
	int id = 0;
	cout << "请输入要修改的员工编号：";
	cin >> id;
	int ret = isExist(id);
	if (ret >= 0) //如果存在
	{
		delete mEmpArry[ret];
		Workers* w = NULL;
		//mEmpArry[ret]->mNum = ret;
		string name;
		cout << "输入要修改名字：";
		cin >> name;
		//mEmpArry[ret]->mName = name;
		cout << "请输入要修改级别：\n"
			"1.普通员工  2.经理  3.老板 \n";
		int level = 0;
		cin >> level;
		switch (level)
		{
		case 1:  //员工    
			w = new  Employees(id, name, level);
			break;
		case 2:  //经理
			w = new  Manger(id, name, level);
			break;
		case 3:  //老板
			w = new  Boss(id, name, level);
			break;
		default:
			cout << "输错了\n";
			break;
		}
		mEmpArry[ret] = w;
		cout << "修改成功\n";
		//delete w;
		save(); //保存数据至文件
	}
	else {
		cout << "不存在\n";
	}
	system("pause");
	system("cls");
}
void EmployeeManagement::mFind()
{
	if (mFilsIsEmpty)
	{
		cout << "文件为空或不存在\n";
		//system("pause");
		return;
	}
	cout << "1.按编号查找\t2.按姓名查找\n";
	int input = 0;
	cin >> input;  
	if (input == 1)
	{
		cout << "请输入编号：";
		int id;
		cin >> id;
		int ret = isExist(id);
		if (ret >= 0) //如果存在
		{
			cout << "编号：" << id << "\t姓名：" 
				<< mEmpArry[ret]->mName 
				<< "\t级别：" << mEmpArry[ret]->mLevel << endl;
		}
		else {
			cout << "查无此人\n";
		}
	}
	else if (input == 2)
	{
		cout << "请输入姓名：";
		string name;
		cin >> name;
		int ret = isExistName(name);
		if (ret >= 0) //如果存在
		{
			cout << "编号：" << ret << "\t姓名："
				<< mEmpArry[ret]->mName
				<< "\t级别：" << mEmpArry[ret]->mLevel << endl;
		}
		else {
			cout << "查无此人\n";
		}
	}
}
int EmployeeManagement::isExistName(string name)
{
	for (int i = 0; i < mENum; i++)
	{
		if (mEmpArry[i]->mName == name)
		{
			return i;
		}
	}
	return -1;
}
void EmployeeManagement::eSortNum()
{
	if (mFilsIsEmpty)
	{
		cout << "文件为空或不存在\n";
		//system("pause");
		return;
	}
	for(int j = 0;j < mENum - 1;j++)
	{
		for (int i = 0; i < mENum - 1 - j; i++)
		{
			if (mEmpArry[i]->mNum < mEmpArry[i + 1]->mNum)
			{
				Workers* t = mEmpArry[i];
				mEmpArry[i] = mEmpArry[i + 1];
				mEmpArry[i + 1] = t;
			}
		}
	}
	save();
	system("pause");
	system("cls");
}
void EmployeeManagement::mDelAll()
{
	ofstream ofs(FILENAME, ios::trunc);   //清空文件
	ofs.close();
	//if()
	//this->~EmployeeManagement();
	//EmployeeManagement::~EmployeeManagement();
	eFree();
}