#pragma once
#include <iostream>
#include "workers.h"
#include <fstream>
#define FILENAME "empFile.txt"
using namespace std;
class EmployeeManagement
{
public:
	EmployeeManagement();
	~EmployeeManagement();
	 void eFree();//释放空间
	void menu();
	void mExit();
	void add();
	void show();
	void showEmp();
	void save();
	void mDelEmp();
	void mDelAll(); //删除所有数据
	int isExist(int id); //按编号查找
	int isExistName(string name); //按名字查找
	int fileFrom();//从文件中读取数据
	int get_mENum();   //文件数据输入到内存
	int mENum; //职工数量
	void mChange();
	void mFind();
	void eSortNum();

	Workers** mEmpArry;  //职工数组
	bool mFilsIsEmpty;  //空时为true;
};

