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
	int get_mENum();  //�鿴�ļ��й��м�������
	int fileFrom(); //��Ӳ����д���ݵ��ڴ�
	void mDelAll();  //����ļ�
	void eFree(); //�ͷſռ�

	int mmNum;  //���鳤��
	Money** mmArry;
	//double mmBalance;  //�����
	double mmGrossIncome; //������
	double mmTotalExpend;  //��֧��
	bool mFilsIsEmpty;  //��ʱΪtrue;


};