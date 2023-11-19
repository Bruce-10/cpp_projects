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
		cout << "请选择：";
		cin >> input;
		switch (input)
		{
		case 1 ://增
			e1.add();
			e1.show();
			//e1.get_mENum();
			break;
			
		case 2 ://删
			e1.mDelEmp();
			break;	
		case 3://查
		{
			e1.mFind();
			break;
		}
		case 4://改
			e1.mChange();
			break;
		case 5://显示
			e1.showEmp();
			break;
		case 6://排序
			e1.eSortNum();
			break;
		case 7://清空
			e1.mDelAll();
			break;
		case 0://退出
			cout << "欢迎下次使用\n";
			//system("pause");
			break;
		default:
			system("cls");
			break;
		}

	} while (input);

}