#include "employees.h"

 void Employees::showInfor()
 {
     cout << "我是" << getJob() << ",叫:" << mName << ",级别：" << mLevel << ",编号：" << mNum << endl;
     //cout << "我是"<<getJob()<<",叫:"<<getMName()<<",级别："<<getMLevel()<<",编号："<<getMNum()<<endl;
 }
string Employees::getJob()
 {
 	return string("员工");
 }
Employees::Employees(int num, string name, int level)
 {
 	mNum = num;
 	mName = name;
 	mLevel = level;
 }