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
		cout << "��ѡ��";
		cin >> input;
		switch (input) {
		case 1:  //����
			mm1.add();
			break;
		case 2:  //֧��
			mm1.expend();
			break;
		case 3:  //�˱�
			mm1.show();
			break;
		case 4:  //����ļ�
			mm1.mDelAll();
			break;
		case 0: //�˳�
			mm1.save();
			break;
		default:
			cout << "�����\n";
			break;
		}
	} while (input);
}