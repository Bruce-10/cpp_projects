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

	//构造函数
	SpeechManager();

	//析构函数
	~SpeechManager();

	//菜单显示
	void showMenu();

	//成员属性
	
	//初始化成员属性
	void initSpeech();

	//创建选手
	void createSpeaker();

	//比赛流程的函数
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届得分
	void showRecord();

	//清空记录
	void clearRecord();

	//文件为空的标志
	bool fileIsEmpty;

	//往届记录
	map<int, vector<string>> mRecord;

	//第一轮比赛的参赛选手
	vector<int> v1;

	//第2轮比赛的参赛选手
	vector<int> v2;

	//决赛选手
	vector<int> vVictory;

	//编号&姓名
	map<int, Speaker> mSpeaker;

	//比赛的轮数
	int mIndex;

};
