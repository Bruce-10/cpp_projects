#pragma once
#include <string>
#include <iostream>
#include "boss.h"
#include "workers.h"
using namespace std;
class Boss : public Workers
{
public:
	virtual void showInfor();
	virtual string getJob();
	//const char* getJob();
	Boss(int num, string name, int level);
};

