#include "boss.h"

void Boss::showInfor()
{
    cout << "����" << getJob() << ",��:" << mName << ",����" << mLevel << ",��ţ�" << mNum << endl;
}
string Boss::getJob()
{
    return string("�ϰ�");
}
Boss::Boss(int num, string name, int level)
{
    mNum = num;
    mName = name;
    mLevel = level;
}