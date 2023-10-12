#include <iostream>
using namespace std;
#include "speechManager.h"
#include "speaker.h"


//测试
void test(SpeechManager &sm) {
	for (auto x : sm.mSpeaker) {
		cout << "姓名:" << x.second.mName << ", "
			<< "编号: " << x.first << " ,"
			<< "第一轮得分:" << x.second.mScore[0] << ", "
			<< "第二轮得分:" << x.second.mScore[1] << "\n";
	}
	cout << endl;
}

int main()
{
	srand((unsigned int)time(NULL));	//随机数种子
	SpeechManager sm;

	//测试
	//test(sm);

	//功能选择
	int choice;
	while (true) {
		sm.showMenu();
		cout << "请选择(0-3):";
		cin >> choice;
		
		switch (choice) {
			case 1 :
				//抽签
				sm.startSpeech();
				//开始演讲比赛
				break;
			case 2 :
				//查看往届记录
				sm.showRecord();
				break;
			case 3 :
				//清空比赛记录
				sm.clearRecord();
				break;
			case 0 :
				//退出
				goto mExit;
			default:
				cout << "输错了, 请重输\n";
				break;
		}
	}

	mExit:  //goto语句

	system("pause");
	return 0;
}