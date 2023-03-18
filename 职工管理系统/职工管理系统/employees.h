#pragma once
#include <string>
#include <iostream>
#include "workers.h"
using namespace std;
class Employees : public Workers
{
public:
	virtual void showInfor();
	virtual string getJob();
	//const char* getJob();
	Employees(int num, string name, int level);
};

