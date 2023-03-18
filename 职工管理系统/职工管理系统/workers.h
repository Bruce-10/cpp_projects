//#pragma once
////#include <string>
//#include <iostream>
//using namespace std;
//class Workers
//{
//public:
//	Workers(int num,  char* name, int level);
//	//~Workers();
//	virtual void dscriptionResponsibilities() = 0;
//	virtual void jobTitle() = 0;
//	virtual const char* getJob() = 0;
//	int getMNum();
//	char* getMName();
//	int getMLevel();
//	Workers();
//
//private:
//	int mNum;
//	char *mName;
//	//string mName;
//	int mLevel;
//};
//class OrdinaryEmployees :public Workers
//{
//public:
//	virtual void dscriptionResponsibilities();
//	virtual void jobTitle();
//	const char* getJob();
//	OrdinaryEmployees(int num, char* name, int level);
//};
//class Manger :public Workers
//{
//public:
//	virtual void dscriptionResponsibilities();
//	virtual void jobTitle();
//	const char* getJob();
//
//};
//class Boss :public Workers
//{
//public:
//	virtual void dscriptionResponsibilities();
//	virtual void jobTitle();
//	const char* getJob();
//
//};

//2
#pragma once
#include <iostream>
#include <string>
using namespace std;
class Workers
{
public:
	
	virtual void showInfor() = 0;
	virtual string getJob() = 0;
	//virtual const char* getJob() = 0;

	int mNum;
	string mName;
	int mLevel;
};