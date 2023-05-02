#include <iostream>
using namespace std;
#include "wokers.h"
#include <vector>
#include <string>
#include <map>
#include <ctime>

/*
需求分析:
●随机给10名员工分配部门]和工资
●公司今天招聘了10个员工(ABCDEFGHIJ) ，10名员工进入公司之后，需要指派员工在那个部门工作
●员工信息有:姓名工资组成;部门分为:测试、美术、研发
●随机给10名员工分配部门]和工资
●通过multimap进行信息的插入key(部门门编号) value(员工)
●分部门显示员工信息


实现步骤
1.创建10名员工，放到vector中
2.遍历vector容器，取出每个员工，进行随机分组
3.分组后，将员工部门编号作为key,具体员工作为value,放入到multimap容器中
4.分部门显示员工信息
*/

void creat(vector<Wokers*>& v)
{
	string names = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++) {
		Wokers *w = new Wokers();
		string name = "员工";
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
	vs.emplace_back("开发:");
	vs.emplace_back("测试:");

	for (int i = 1; i <= 3; i++) {
		cout << vs[i - 1] << endl;
		//找到目标键值
		multimap<int, Wokers*>::const_iterator pos = m.find(i);
		//统计键值
		int n = m.count(i);
		//打印
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
	//创建员工
	creat(vWorks);

	multimap<int, Wokers*> mWoker;
	//员工分组
	grouping(vWorks, mWoker);

	printWorker(mWoker);

	system("pause");
	return 0;
}