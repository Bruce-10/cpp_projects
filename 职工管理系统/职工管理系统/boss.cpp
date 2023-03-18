#include "boss.h"

void Boss::showInfor()
{
    cout << "我是" << getJob() << ",叫:" << mName << ",级别：" << mLevel << ",编号：" << mNum << endl;
}
string Boss::getJob()
{
    return string("老板");
}
Boss::Boss(int num, string name, int level)
{
    mNum = num;
    mName = name;
    mLevel = level;
}