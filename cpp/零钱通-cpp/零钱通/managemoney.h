#pragma once
#include <iostream>
#include "money.h"

using namespace std;

class MansgeMoney
{
public:
	void menu();
	void add();
	void expend();
	void show();
	MansgeMoney();
	~MansgeMoney();
	void save();
	int get_mENum();  //查看文件中共有几条数据
	int fileFrom(); //从硬盘中写数据到内存
	void mDelAll();  //清空文件
	void eFree(); //释放空间

	int mmNum;  //数组长度
	Money** mmArry;
	//double mmBalance;  //总余额
	double mmGrossIncome; //总收入
	double mmTotalExpend;  //总支出
	bool mFilsIsEmpty;  //空时为true;


};