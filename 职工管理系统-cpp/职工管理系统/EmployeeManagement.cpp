
#include "EmployeeManagement.h"
#include "employees.h"
#include "manger.h"
#include "boss.h"
#include "workers.h"

EmployeeManagement::EmployeeManagement()
{
	//1.�ļ�������
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open()) //�ļ�������
	{
		mFilsIsEmpty = true;
		mEmpArry = NULL;
		mENum = 0;
		ifs.close();

		cout << "�ļ�������\t";
		return;
	}
	//2.�ļ����ڵ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		mFilsIsEmpty = true;
		mEmpArry = NULL;
		mENum = 0;
		ifs.close();
		cout << "�ļ�����,��Ϊ��\t";
		return;
	}
	//3.�ļ������Ҳ�Ϊ��
	//else
	//{
	//	//fileFrom();
	//	mFilsIsEmpty = false;
	//	mENum = get_mENum();
	//	ifs.close();
	//	cout << "�ļ�����,��Ϊ��\n";
	//	return;
	//}
	//else
	//{
	//	//mFilsIsEmpty = false;
	//	////mEmpArry = NULL;
	//	//mENum = get_mENum();
	//	//ifs.close();
	//	//cout << "�ļ�����,��Ϊ��\n";
	//	//return;
	//}
	get_mENum();
	//fileFrom();
	mEmpArry = new Workers *[mENum];
	fileFrom();
	show();
}
EmployeeManagement::~EmployeeManagement()
{
	eFree();
	
}
void EmployeeManagement::eFree()
{
	if (mEmpArry != NULL)
	{
		for (int i = 0; i < mENum; i++)
		{
			if (mEmpArry[i] != NULL)
			{
				delete mEmpArry[i];
				mEmpArry[i] = NULL;
			}
		}
		mFilsIsEmpty = true;
		mENum = 0;
		delete[] mEmpArry;
		mEmpArry = NULL;
	}
}
void EmployeeManagement::menu()
{
	cout << "--------------------------------------------\n";
	cout << "1.��\t2.ɾ\n";
	cout << "3.��\t4.��\n";
	cout << "5.��ʾ\t6.���ձ������\n";
	cout << "7.���\t0.�˳�\n";
	cout << "--------------------------------------------\n";
}
void EmployeeManagement::mExit()
{
	cout << "��ӭ�´�ʹ��\n";
	system("pause");
	exit(0);
}
void EmployeeManagement::add()
{
	mENum++;
	//Workers** mEmpArry;
		//mEmpArry = new Workers *[mENum];
	Workers** newArry = new Workers * [mENum];
	if (mEmpArry != NULL) {  //��������
		for (int i = 0; i < mENum; i++)
		{
			newArry[i] = mEmpArry[i];
		}
	}
	int num = 0;
	string name;
	cout << "�����ţ�";
	cin >> num;
	cout << "�������֣�";
	cin >> name;

	cout << "�����뼶��\n"
		"1.��ͨԱ��  2.����  3.�ϰ� \n";
	int level = 0;
	cin >> level;
	Workers* w = NULL;
	switch (level)
	{
	case 1:  //Ա��    
		//Employees::Employees(int num, string name, int level)
		w = new  Employees(num, name, level);
		break;
	case 2:  //����
		w = new  Manger(num, name, level);
		break;
	case 3:  //�ϰ�
		w = new  Boss(num, name, level);
		break;
	default:
		cout << "�����\n";
		return;
	}
	newArry[mENum - 1] = w;
	delete[] mEmpArry;
	mEmpArry = newArry;
	//delete[] newArry;    //������ֹ
	cout << "��ӳɹ�\n";
	save(); //�����������ļ�
	mFilsIsEmpty = false;
	system("pause");
	system("cls");

}
void EmployeeManagement::show()
{
	for (int i = 0; i < mENum; i++)
	{
	
		cout << "���\t����\t����\n";
		cout << mEmpArry[i]->mNum<< "\t" << mEmpArry[i]->mName << "\t" << mEmpArry[i]->mLevel << endl;

	}
	//save(); //�����������ļ�
	//mFilsIsEmpty = false;

	//cout << mENum<<endl;

}
void EmployeeManagement::save()
{
	ofstream ofs;
	ofs.open (FILENAME, ios::out);
	for (int i = 0; i < mENum; i++)
	{
		/*ofs << "  " << "���\t" << "����\t" << "����\n"
			<<i<<'.' */
			ofs<< mEmpArry[i]->mNum << "\t"
			<< mEmpArry[i]->mName << "\t" 
			<< mEmpArry[i]->mLevel << endl;
	}
	ofs.close();
}
//�ļ��������뵽�ڴ�
int EmployeeManagement::get_mENum()
{
	ifstream ifs;
	//ios::in���ļ������뷽ʽ�򿪣��ļ��������뵽�ڴ棩
	ifs.open (FILENAME, ios::in);
	int num;
	string name;
	int levle;
	int cont = 0;
	while (ifs >> num && ifs >> name && ifs >> levle)
	{
		cont++;
	}
	ifs.close();
	mENum = cont;
	cout << "get_mENum��������" << cont << endl;
	return cont;
}
int EmployeeManagement::fileFrom()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int num;
	string name;
	int level;
	int index = 0;
	while (ifs >> num && ifs >> name && ifs >> level)
	{
		Workers* w = NULL;
		switch (level)
		{
		case 1:  //Ա��    
			//Employees::Employees(int num, string name, int level)
			w = new  Employees(num, name, level);
			break;
		case 2:  //����
			w = new  Manger(num, name, level);
			break;
		case 3:  //�ϰ�
			w = new  Boss(num, name, level);
			break;
		}
		//mEmpArry = new Workers * [mENum];
		mEmpArry[index] = w;
		index++;
	}
	mENum = index;
	cout << "fileFrom��������" << index << endl;
	return index;
}

void EmployeeManagement::showEmp()
{
	if (mFilsIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���\n";
	}
	else
	{
		for (int i = 0; i < mENum; i++)
		{
			mEmpArry[i]->showInfor();
		}
		cout << "Ա��������" << mENum << endl;
	}
}
void EmployeeManagement::mDelEmp()
{
	if (mFilsIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���\n";
		//system("pause");
		return;
	}
	int id = 0;
	cout << "������Ҫɾ����Ա����ţ�";
	cin >> id;
	int ret = isExist(id);
	if (ret >= 0) //�������
	{
		mEmpArry[ret]->mNum = mEmpArry[mENum - 1]->mNum;
		mEmpArry[ret]->mName = mEmpArry[mENum - 1]->mName;
		mEmpArry[ret]->mLevel = mEmpArry[mENum - 1]->mLevel;
		mENum--;
		save();
	}
	else {
		cout << "������\n";
	}
	system("pause");
	system("cls");

}
int EmployeeManagement::isExist(int id)
{
	for (int i = 0; i < mENum; i++)
	{
		if (mEmpArry[i]->mNum == id)
		{
			return i;
		}
	}
	return -1;
}
void EmployeeManagement::mChange()
{
	if (mFilsIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���\n";
		return;
	}
	int id = 0;
	cout << "������Ҫ�޸ĵ�Ա����ţ�";
	cin >> id;
	int ret = isExist(id);
	if (ret >= 0) //�������
	{
		delete mEmpArry[ret];
		Workers* w = NULL;
		//mEmpArry[ret]->mNum = ret;
		string name;
		cout << "����Ҫ�޸����֣�";
		cin >> name;
		//mEmpArry[ret]->mName = name;
		cout << "������Ҫ�޸ļ���\n"
			"1.��ͨԱ��  2.����  3.�ϰ� \n";
		int level = 0;
		cin >> level;
		switch (level)
		{
		case 1:  //Ա��    
			w = new  Employees(id, name, level);
			break;
		case 2:  //����
			w = new  Manger(id, name, level);
			break;
		case 3:  //�ϰ�
			w = new  Boss(id, name, level);
			break;
		default:
			cout << "�����\n";
			break;
		}
		mEmpArry[ret] = w;
		cout << "�޸ĳɹ�\n";
		//delete w;
		save(); //�����������ļ�
	}
	else {
		cout << "������\n";
	}
	system("pause");
	system("cls");
}
void EmployeeManagement::mFind()
{
	if (mFilsIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���\n";
		//system("pause");
		return;
	}
	cout << "1.����Ų���\t2.����������\n";
	int input = 0;
	cin >> input;  
	if (input == 1)
	{
		cout << "�������ţ�";
		int id;
		cin >> id;
		int ret = isExist(id);
		if (ret >= 0) //�������
		{
			cout << "��ţ�" << id << "\t������" 
				<< mEmpArry[ret]->mName 
				<< "\t����" << mEmpArry[ret]->mLevel << endl;
		}
		else {
			cout << "���޴���\n";
		}
	}
	else if (input == 2)
	{
		cout << "������������";
		string name;
		cin >> name;
		int ret = isExistName(name);
		if (ret >= 0) //�������
		{
			cout << "��ţ�" << ret << "\t������"
				<< mEmpArry[ret]->mName
				<< "\t����" << mEmpArry[ret]->mLevel << endl;
		}
		else {
			cout << "���޴���\n";
		}
	}
}
int EmployeeManagement::isExistName(string name)
{
	for (int i = 0; i < mENum; i++)
	{
		if (mEmpArry[i]->mName == name)
		{
			return i;
		}
	}
	return -1;
}
void EmployeeManagement::eSortNum()
{
	if (mFilsIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���\n";
		//system("pause");
		return;
	}
	for(int j = 0;j < mENum - 1;j++)
	{
		for (int i = 0; i < mENum - 1 - j; i++)
		{
			if (mEmpArry[i]->mNum < mEmpArry[i + 1]->mNum)
			{
				Workers* t = mEmpArry[i];
				mEmpArry[i] = mEmpArry[i + 1];
				mEmpArry[i + 1] = t;
			}
		}
	}
	save();
	system("pause");
	system("cls");
}
void EmployeeManagement::mDelAll()
{
	ofstream ofs(FILENAME, ios::trunc);   //����ļ�
	ofs.close();
	//if()
	//this->~EmployeeManagement();
	//EmployeeManagement::~EmployeeManagement();
	eFree();
}