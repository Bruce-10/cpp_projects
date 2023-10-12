#include <iostream>
#include "money.h"
#include "managemoney.h"

using namespace  std;
void test();

int main()
{
	test();
	return 0;
}

void test()
{
	/*Money m1(234, "eat");
	m1.print();*/
	MansgeMoney mm1;
	int input;
	do {
		mm1.menu();
		cout << "请选择：";
		cin >> input;
		switch (input) {
		case 1:  //收入
			mm1.add();
			break;
		case 2:  //支出
			mm1.expend();
			break;
		case 3:  //账本
			mm1.show();
			break;
		case 4:  //清空文件
			mm1.mDelAll();
			break;
		case 0: //退出
			mm1.save();
			break;
		default:
			cout << "输错了\n";
			break;
		}
	} while (input);
}