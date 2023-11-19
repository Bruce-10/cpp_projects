#include "managemoney.h"
#include <iostream>
#include <string>
#include <fstream>
#define FILENAME "ChangePass.txt"

//#include <time.h>
//#pragma warning( disable : 4996 )
void MansgeMoney::menu()
{
	cout << "-----------------------------------\n";
	cout << "1.收入\t2.支出\n"
		<< "3.账单\t4.清空\n"
		<<"0.退出\n";
	cout << "-----------------------------------\n";
}
MansgeMoney::MansgeMoney()
{
	//1.文件不存在
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open()) //文件不存在
	{
		mFilsIsEmpty = true;
		mmArry = NULL;
		mmNum  = 0;
		ifs.close();

		cout << "文件不存在\n";
		mmGrossIncome = 0;
		mmTotalExpend = 0;
		return;
	}
	//2.文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		mFilsIsEmpty = true;
		mmArry = NULL;
		mmNum = 0;
		ifs.close();
		cout << "文件存在,但为空\t";
		mmGrossIncome = 0;
		mmTotalExpend = 0;
		return;
	}
	get_mENum();  //正常
	mmArry = new Money * [mmNum];
	fileFrom();
	/*mmGrossIncome = 0;
	mmTotalExpend = 0;*/
}
MansgeMoney::~MansgeMoney()
{
	eFree();
}
//expend:0000004ED48FF338
// add:  0000004ED48FF338
//收入
void MansgeMoney::add()
{
	mmNum++;
	Money** newArry = new Money * [mmNum];
	//cout << "add:" << &newArry<<endl;
	if (mmArry != NULL)
	{
		for (int i = 0; i < mmNum; i++)  //数组阔容
		{
			newArry[i] = mmArry[i];
		}
		//mmArry = newArry;
	}
	Money* m = NULL;
	double money;
	string details;
	cout << "请输入收入的钱：";
	cin >> money;
	if (money < 0) {
		cout << "输错了\n";
		return;
	}
	cout << "请输入明细：";
	cin >> details;
	//time(&(m->mCurtime ) );
	//m->mBalance += money;

	mmGrossIncome += money;
	m = new Money(money, details, mmGrossIncome - mmTotalExpend);
	//mmArry[mmNum- 1] = m;
	newArry[mmNum - 1] = m;
	delete[] mmArry;
	mmArry = newArry;
	system("pause");
	system("cls");
}
//支出
void MansgeMoney::expend()
{
	mmNum++;
	Money** newArry = new Money * [mmNum];
	//cout << "expend:" << &newArry<<endl;

	if (mmArry != NULL)
	{
		for (int i = 0; i < mmNum; i++)  //数组阔容
		{
			newArry[i] = mmArry[i];
		}
		//mmArry = newArry;
	}
	Money* m = NULL;
	double money;
	string details;
	cout << "余额：" << mmGrossIncome - mmTotalExpend << endl;
	cout << "请输入支出的钱：";
	cin >> money;
	if (money > mmGrossIncome - mmTotalExpend)
	{
		cout << "钱不够\n";
		return;
	}
	if (money < 0) {
		cout << "输错了\n";
		return;
	}
	//money *= -1;
	mmTotalExpend += money;
	cout << "请输入明细：";
	cin >> details;
	//time(&(m->mCurtime ) );
	m = new Money(money *= -1, details, mmGrossIncome - mmTotalExpend);
	//mmArry[mmNum- 1] = m;
	newArry[mmNum - 1] = m;
	delete[] mmArry;
	mmArry = newArry;
	system("pause");
	system("cls");
}

void MansgeMoney::show()
{
	//以下注释编译器会报错
	///*time_t timep;
	//time(&timep);
	//char tmp[256];*/
	////strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	//cout << tmp << endl;
	cout << "钱\t明细\t余额\n";
	for (int i = 0; i < mmNum; i++)
	{
		cout << mmArry[i]->mMoney << "\t"
			<< mmArry[i]->mDetails <<"\t"
			<< "余额：" << mmArry[i]->mBalance << endl;
			//<< ctime_s( (mmArry[i]->mCurtime) );
	}
	cout<<"总收入："<< mmGrossIncome<<"\t"
		<<"总支出："<<mmTotalExpend<<"\t"
		<< "总余额：" << mmGrossIncome - mmTotalExpend << endl;
	system("pause");
	system("cls");
}

void MansgeMoney::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->mmNum; i++) {
		ofs << mmArry[i]->mMoney << "\t"
			<< mmArry[i]->mDetails << "\t"
			<< mmArry[i]->mBalance << "\n";
	}
	ofs.close();
	cout << "保存成功\n";
}

//查看文件中共有几条数据
int MansgeMoney::get_mENum()
{
	ifstream ifs;
	//ios::in：文件以输入方式打开（文件数据输入到内存）
	ifs.open(FILENAME, ios::in);
	double money;
	double balance;
	string details;
	int cont = 0;
	while (ifs >> money && ifs >> details && ifs >> balance && ifs)
	{
		cont++;
	}
	ifs.close();
	this->mmNum = cont;
	cout << "数据数：" << cont << endl;
	return cont;
}
int MansgeMoney::fileFrom()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	double money;
	double balance;
	string details;
	int index = 0;
	while (ifs >> money && ifs >> details && ifs >> balance && ifs)
	{
		Money* w = new Money(money, details, balance);
		//m->mBalance = mmGrossIncome - mmTotalExpend;
		mmArry[index] = w;
		index++;
		if (money >= 0) {
			mmGrossIncome += money;
		}
		else {
			mmTotalExpend += (money *= -1);
		}
	}
	//cout << "fileFrom数据数：" << index << endl;
	return index;
}
//清空文件
void MansgeMoney::mDelAll()
{
	ofstream ofs(FILENAME, ios::trunc);   //清空文件
	ofs.close();
	eFree(); 
}
//释放空间
void MansgeMoney::eFree()
{
	if (mmArry != NULL)
	{
		for (int i = 0; i < mmNum; i++)
		{
			if (mmArry[i] != NULL)
			{
				delete mmArry[i];
				mmArry[i] = NULL;
			}
		}
		mFilsIsEmpty = true;
		mmNum = 0;
		delete[] mmArry;
		mmArry = NULL;
		mmGrossIncome = 0;
		mmTotalExpend = 0;
	}
	system("pause");
	system("cls");
}