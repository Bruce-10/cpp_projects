#include <iostream>
using namespace std;
#include "speechManager.h"
#include "speaker.h"


//����
void test(SpeechManager &sm) {
	for (auto x : sm.mSpeaker) {
		cout << "����:" << x.second.mName << ", "
			<< "���: " << x.first << " ,"
			<< "��һ�ֵ÷�:" << x.second.mScore[0] << ", "
			<< "�ڶ��ֵ÷�:" << x.second.mScore[1] << "\n";
	}
	cout << endl;
}

int main()
{
	srand((unsigned int)time(NULL));	//���������
	SpeechManager sm;

	//����
	//test(sm);

	//����ѡ��
	int choice;
	while (true) {
		sm.showMenu();
		cout << "��ѡ��(0-3):";
		cin >> choice;
		
		switch (choice) {
			case 1 :
				//��ǩ
				sm.startSpeech();
				//��ʼ�ݽ�����
				break;
			case 2 :
				//�鿴�����¼
				sm.showRecord();
				break;
			case 3 :
				//��ձ�����¼
				sm.clearRecord();
				break;
			case 0 :
				//�˳�
				goto mExit;
			default:
				cout << "�����, ������\n";
				break;
		}
	}

	mExit:  //goto���

	system("pause");
	return 0;
}