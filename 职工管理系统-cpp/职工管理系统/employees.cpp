#include "employees.h"

 void Employees::showInfor()
 {
     cout << "����" << getJob() << ",��:" << mName << ",����" << mLevel << ",��ţ�" << mNum << endl;
     //cout << "����"<<getJob()<<",��:"<<getMName()<<",����"<<getMLevel()<<",��ţ�"<<getMNum()<<endl;
 }
string Employees::getJob()
 {
 	return string("Ա��");
 }
Employees::Employees(int num, string name, int level)
 {
 	mNum = num;
 	mName = name;
 	mLevel = level;
 }