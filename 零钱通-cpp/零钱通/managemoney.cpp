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
	cout << "1.����\t2.֧��\n"
		<< "3.�˵�\t4.���\n"
		<<"0.�˳�\n";
	cout << "-----------------------------------\n";
}
MansgeMoney::MansgeMoney()
{
	//1.�ļ�������
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open()) //�ļ�������
	{
		mFilsIsEmpty = true;
		mmArry = NULL;
		mmNum  = 0;
		ifs.close();

		cout << "�ļ�������\n";
		mmGrossIncome = 0;
		mmTotalExpend = 0;
		return;
	}
	//2.�ļ����ڵ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		mFilsIsEmpty = true;
		mmArry = NULL;
		mmNum = 0;
		ifs.close();
		cout << "�ļ�����,��Ϊ��\t";
		mmGrossIncome = 0;
		mmTotalExpend = 0;
		return;
	}
	get_mENum();  //����
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
//����
void MansgeMoney::add()
{
	mmNum++;
	Money** newArry = new Money * [mmNum];
	//cout << "add:" << &newArry<<endl;
	if (mmArry != NULL)
	{
		for (int i = 0; i < mmNum; i++)  //��������
		{
			newArry[i] = mmArry[i];
		}
		//mmArry = newArry;
	}
	Money* m = NULL;
	double money;
	string details;
	cout << "�����������Ǯ��";
	cin >> money;
	if (money < 0) {
		cout << "�����\n";
		return;
	}
	cout << "��������ϸ��";
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
//֧��
void MansgeMoney::expend()
{
	mmNum++;
	Money** newArry = new Money * [mmNum];
	//cout << "expend:" << &newArry<<endl;

	if (mmArry != NULL)
	{
		for (int i = 0; i < mmNum; i++)  //��������
		{
			newArry[i] = mmArry[i];
		}
		//mmArry = newArry;
	}
	Money* m = NULL;
	double money;
	string details;
	cout << "��" << mmGrossIncome - mmTotalExpend << endl;
	cout << "������֧����Ǯ��";
	cin >> money;
	if (money > mmGrossIncome - mmTotalExpend)
	{
		cout << "Ǯ����\n";
		return;
	}
	if (money < 0) {
		cout << "�����\n";
		return;
	}
	//money *= -1;
	mmTotalExpend += money;
	cout << "��������ϸ��";
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
	//����ע�ͱ������ᱨ��
	///*time_t timep;
	//time(&timep);
	//char tmp[256];*/
	////strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	//cout << tmp << endl;
	cout << "Ǯ\t��ϸ\t���\n";
	for (int i = 0; i < mmNum; i++)
	{
		cout << mmArry[i]->mMoney << "\t"
			<< mmArry[i]->mDetails <<"\t"
			<< "��" << mmArry[i]->mBalance << endl;
			//<< ctime_s( (mmArry[i]->mCurtime) );
	}
	cout<<"�����룺"<< mmGrossIncome<<"\t"
		<<"��֧����"<<mmTotalExpend<<"\t"
		<< "����" << mmGrossIncome - mmTotalExpend << endl;
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
	cout << "����ɹ�\n";
}

//�鿴�ļ��й��м�������
int MansgeMoney::get_mENum()
{
	ifstream ifs;
	//ios::in���ļ������뷽ʽ�򿪣��ļ��������뵽�ڴ棩
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
	cout << "��������" << cont << endl;
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
	//cout << "fileFrom��������" << index << endl;
	return index;
}
//����ļ�
void MansgeMoney::mDelAll()
{
	ofstream ofs(FILENAME, ios::trunc);   //����ļ�
	ofs.close();
	eFree(); 
}
//�ͷſռ�
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