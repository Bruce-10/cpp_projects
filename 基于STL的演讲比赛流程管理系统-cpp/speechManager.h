#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "speaker.h"
#include <map>
#include <algorithm>
#include <set>
#include <deque>
#include <numeric>
#include <fstream>




class SpeechManager {
public:

	//���캯��
	SpeechManager();

	//��������
	~SpeechManager();

	//�˵���ʾ
	void showMenu();

	//��Ա����
	
	//��ʼ����Ա����
	void initSpeech();

	//����ѡ��
	void createSpeaker();

	//�������̵ĺ���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ����÷�
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//�ļ�Ϊ�յı�־
	bool fileIsEmpty;

	//�����¼
	map<int, vector<string>> mRecord;

	//��һ�ֱ����Ĳ���ѡ��
	vector<int> v1;

	//��2�ֱ����Ĳ���ѡ��
	vector<int> v2;

	//����ѡ��
	vector<int> vVictory;

	//���&����
	map<int, Speaker> mSpeaker;

	//����������
	int mIndex;

};
