#pragma once
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Money
{
public:
	//time(&mCurtime);
	//Money(double money, string details) :mMoney(money), mDetails(details) //time(&mCurtime)
	//{
	//	/*time(&mCurtime);*/
	//}
	//void print();
	//Money();
	Money(double money, string details, double balance);
	
//private:
	double mMoney;
	string mDetails;
	double mBalance;  //”‡∂Ó
	//time_t mCurtime;
	//time(&mCurtime);
	/*time(&curtime);
	cout << ctime(&curtime);*/
};
