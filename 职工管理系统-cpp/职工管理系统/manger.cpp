#include "manger.h"

void Manger::showInfor()
{
    cout << "����" << getJob() << ",��:" << mName << ",����" << mLevel << ",��ţ�" << mNum << endl;
}
string Manger::getJob()
{
    return string("����");
}
Manger::Manger(int num, string name, int level)
{
    mNum = num;
    mName = name;
    mLevel = level;
}