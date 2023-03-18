#pragma once
#include <string>
#include <iostream>
#include "manger.h"
#include "workers.h"
using namespace std;
class Manger : public Workers
{
public:
	virtual void showInfor();
	virtual string getJob();
	//const char* getJob();
	Manger(int num, string name, int level);
};

