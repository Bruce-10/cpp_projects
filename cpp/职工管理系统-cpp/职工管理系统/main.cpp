#include "EmployeeManagement.h"
#include "workers.h"  
#include "employees.h"
#include "manger.h"
#include "boss.h"

void test();

int main()
{
	/*Workers* w1 = new Employees (1,"123", 1);
	w1->showInfor();
	Workers* w2 = new Manger(2, "lihua", 2);
	w2->showInfor();
	Workers* w3 = new Boss(2, "lihua", 2);
	w3->showInfor();*/
	test();
	//system("pause");
	return 0;
}
void test()
{
	EmployeeManagement e1;
	int input = 0;
	do
	{
		e1.menu();
		cout << "��ѡ��";
		cin >> input;
		switch (input)
		{
		case 1 ://��
			e1.add();
			e1.show();
			//e1.get_mENum();
			break;
			
		case 2 ://ɾ
			e1.mDelEmp();
			break;	
		case 3://��
		{
			e1.mFind();
			break;
		}
		case 4://��
			e1.mChange();
			break;
		case 5://��ʾ
			e1.showEmp();
			break;
		case 6://����
			e1.eSortNum();
			break;
		case 7://���
			e1.mDelAll();
			break;
		case 0://�˳�
			cout << "��ӭ�´�ʹ��\n";
			//system("pause");
			break;
		default:
			system("cls");
			break;
		}

	} while (input);

}