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
	 void eFree();//�ͷſռ�
	void menu();
	void mExit();
	void add();
	void show();
	void showEmp();
	void save();
	void mDelEmp();
	void mDelAll(); //ɾ����������
	int isExist(int id); //����Ų���
	int isExistName(string name); //�����ֲ���
	int fileFrom();//���ļ��ж�ȡ����
	int get_mENum();   //�ļ��������뵽�ڴ�
	int mENum; //ְ������
	void mChange();
	void mFind();
	void eSortNum();

	Workers** mEmpArry;  //ְ������
	bool mFilsIsEmpty;  //��ʱΪtrue;
};

