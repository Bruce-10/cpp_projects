#include <iostream>
using namespace std;
#include "wokers.h"
#include <vector>
#include <string>
#include <map>
#include <ctime>

/*
�������:
�������10��Ա�����䲿��]�͹���
��˾������Ƹ��10��Ա��(ABCDEFGHIJ) ��10��Ա�����빫˾֮����Ҫָ��Ա�����Ǹ����Ź���
��Ա����Ϣ��:�����������;���ŷ�Ϊ:���ԡ��������з�
�������10��Ա�����䲿��]�͹���
��ͨ��multimap������Ϣ�Ĳ���key(�����ű��) value(Ա��)
��ֲ�����ʾԱ����Ϣ


ʵ�ֲ���
1.����10��Ա�����ŵ�vector��
2.����vector������ȡ��ÿ��Ա���������������
3.����󣬽�Ա�����ű����Ϊkey,����Ա����Ϊvalue,���뵽multimap������
4.�ֲ�����ʾԱ����Ϣ
*/

void creat(vector<Wokers*>& v)
{
	string names = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++) {
		Wokers *w = new Wokers();
		string name = "Ա��";
		name += names[i];
		w->mName = name;
		w->mWage = rand() % 5000 + 5000;  // 5000-9999
		v.emplace_back(w);
	}
}

void grouping(const vector<Wokers*>& v, multimap<int, Wokers*>& m)
{
	for (vector<Wokers*>::const_iterator it = v.begin(); it != v.end(); it++) {
		int id = rand() % 3 + 1;  //1-3
		m.insert(pair<int, Wokers*>(id, *it));
	}
}

void printWorker(const multimap<int, Wokers*>& m)
{
	vector<string> vs;
	vs.emplace_back("UI:");
	vs.emplace_back("����:");
	vs.emplace_back("����:");

	for (int i = 1; i <= 3; i++) {
		cout << vs[i - 1] << endl;
		//�ҵ�Ŀ���ֵ
		multimap<int, Wokers*>::const_iterator pos = m.find(i);
		//ͳ�Ƽ�ֵ
		int n = m.count(i);
		//��ӡ
		while (n--) {
			cout << pos->second->mName << " "
				<< pos->second->mWage << " "
				<< pos->first << endl;
			pos++;
		}
		cout << "---------------------------------------\n";
	}
}

int main()
{
	srand((unsigned)time(0));

	vector<Wokers*> vWorks;
	//����Ա��
	creat(vWorks);

	multimap<int, Wokers*> mWoker;
	//Ա������
	grouping(vWorks, mWoker);

	printWorker(mWoker);

	system("pause");
	return 0;
}