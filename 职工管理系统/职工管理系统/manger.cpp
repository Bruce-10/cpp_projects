#include "manger.h"

void Manger::showInfor()
{
    cout << "我是" << getJob() << ",叫:" << mName << ",级别：" << mLevel << ",编号：" << mNum << endl;
}
string Manger::getJob()
{
    return string("经理");
}
Manger::Manger(int num, string name, int level)
{
    mNum = num;
    mName = name;
    mLevel = level;
}