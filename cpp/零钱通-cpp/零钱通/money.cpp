#include "money.h"
//void Money::print()
//{
//	cout << mMoney << "  " << mDetails /*<< "  " << ctime(&mCurtime)*/;
//
//}
//Money::Money()
//{
//}
Money::Money(double money, string details, double balance)
{
	mMoney = money;
	mDetails = details;
	mBalance = balance;
	//time(&mCurtime);
}