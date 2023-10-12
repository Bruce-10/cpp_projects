#include "speechManager.h"


SpeechManager::SpeechManager() {
	//初始化成员属性
	this->initSpeech();

	//创建参赛选手
	this->createSpeaker();

	//读取往届记录
	this->loadRecord();
}

SpeechManager::~SpeechManager() {

}

//显示菜单
void SpeechManager::showMenu() {
	cout << "**************************************\n"; 
	cout << "*********** 欢迎参加演讲比赛 ********\n";
	cout << "*********** 1. 开始演讲比赛 ********\n";
	cout << "*********** 2. 查看往届记录 ********\n";
	cout << "*********** 3. 清空比赛记录 ********\n";
	cout << "*********** 0. 退出比赛程序 ********\n";
	cout << "**************************************\n";
	cout << endl;
}

//初始化成员属性
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->mSpeaker.clear();
	this->mIndex = 1;
	this->mRecord.clear();
}

//创建选手
void SpeechManager::createSpeaker() {
	string str = "ABCDEFGHIJKL";
	//创建12个选手
	for (int i = 0; i < str.size(); i++) {
		string _name = "选手";
		_name += str[i];

		Speaker sp;
		sp.mName = _name;
		sp.mScore[0] = 0;
		sp.mScore[1] = 0;

		this->v1.emplace_back(1001 + i);
		this->mSpeaker.insert(make_pair(1001 + i, sp));
	}
	//姓名, 编号, 得分
}

//比赛流程的函数
void SpeechManager::startSpeech() {
	
	//第一轮比赛
	//1.抽签
	this->speechDraw();

	//2. 比赛
	this->speechContest();

	//3. 显示晋级结果
	this->showScore();

	//if mIndex = 2, 则结束
	if (mIndex == 2) {
		//保存分数:
		this->saveRecord();
		cout << "本届比赛完毕\n";

//
		//初始化成员属性
		this->initSpeech();

		//创建参赛选手
		this->createSpeaker();

		//读取往届记录
		this->loadRecord();
// //加这几行代码是为了更新本届比赛的数据, 解决查看不到本届记录的bug

		system("pause");
		system("cls");
		return;
	}

	//第二轮比赛
	this->mIndex++;
	startSpeech();
}

//抽签
void SpeechManager::speechDraw() {
	cout << "第<< " << mIndex << " >>轮选手正在抽签\n";
	if (mIndex == 1) {
		//对第一轮的编号随机洗牌
		random_shuffle(v1.begin(), v1.end());
		int len = v1.size();
		for (int i = 0; i < len; i++) {
			cout << v1[i] << " ,";
		}
	}

	else {
		random_shuffle(v2.begin(), v2.end());
		int len = v2.size();
		for (int i = 0; i < len; i++) {
			cout << v2[i] << " ,";
		}
	}
	cout << endl << endl;

}

//比赛
void SpeechManager::speechContest() {
	cout << "第  " << this->mIndex << " 轮比赛\n";
	//所有元素都会根据元素的** 键值** 自动排序,  所以double要在前
	multimap< double, int, greater<double>> groupScore;	//greater为降序

	vector<int> v_src; //比赛人员的容器

	int num = 0;
	mIndex == 1 ? v_src = this->v1 : v_src = this->v2;

	for (auto x : v_src) {
		num++;
		multiset<double> dqe;
		//10个评委打分
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
			dqe.insert(score);
		}
		//计算平均分
		dqe.erase(dqe.begin());
		dqe.erase(--dqe.end());

		//计算总和:`accumulate(iterator beg, iterator end, value);  `
		double sum = accumulate(dqe.begin(), dqe.end(), 0.0f);
		double avg = sum / 8;

		//每个人平均分
		//cout << "编号： " << x  << " 选手： " << this->mSpeaker[x].mName << " 获取平均分为： " << avg << endl;  //打印分数
		this->mSpeaker[x].mScore[this->mIndex - 1] = avg;

		groupScore.insert(make_pair( avg, x));

		if (num % 6 == 0) { //如果比赛完一组
			cout << "第 " << num / 6 << "小组成绩:\n";
			for (auto mp : groupScore) {
				cout << "编号： " << mp.second
					<< " 选手： " << this->mSpeaker[mp.second].mName 
					<< " 分为： " << mp.first << endl;  //打印分数
			}
			int cnt = 3;
			auto it = groupScore.begin();
			while (cnt--) {
				if (this->mIndex == 1) {
					v2.emplace_back(it->second);
				}
				else {
					vVictory.emplace_back(it->second);
				}
				it++;
			}
			groupScore.clear();
			cout << endl;
			
		}
	}
	cout << "第  " << this->mIndex << " 轮比赛完毕\n";
	system("pause");
}


//显示比赛结果
void SpeechManager::showScore() {
	cout << "第  " << this->mIndex << " 轮比赛晋级结果如下\n";

	//临时容器保存选手编号:
	vector<int> v_src;
	v_src = this->mIndex == 1 ? v2 : vVictory;

	//对mSpeaker[v_src[i]].secore进行排序
	multimap< double, int, greater<double>> groupScore;	//greater为降序
	for (auto x : v_src) {
		groupScore.insert(make_pair(this->mSpeaker[x].mScore[mIndex - 1], x));
	}

	//遍历v_src容器, 打印晋级结果
	for (auto mp : groupScore) {
		cout << "编号： " << mp.second
			<< " 选手： " << this->mSpeaker[mp.second].mName
			<< " 分为： " << mp.first << endl;  //打印分数
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

//保存记录
void SpeechManager::saveRecord() {
	/*
	ios::out为写文件而打开文件
	ios::app追加方式写文件
	*/
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	//将每个人的成绩写入文件中
	for (auto x : vVictory) {
		//ofs << x <<"," << this->mSpeaker[x].mScore[1] << "," << endl;
		ofs << x <<"," << this->mSpeaker[x].mScore[1] << ",";
	}
	ofs << endl;

	ofs.close();

	cout << "记录已经保存\n";
	this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord() {
	//ios::in为读文件而打开文件
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在\n";
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;	//先读取一个字符, 判断是否为空
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		//cout << "文件存在, 但为空\n";
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch); //将刚刚读取的字符在放回去, 保证字符的完整性

	string data;
	int index = 0;

	while (ifs >> data) {
		/*
		1002,86.675,1009,81.3,1007,78.55,
		1002,86.675,1009,81.3,1007,78.55,
		*/
		//cout << data << endl;
		vector<string> v;
		int start = 0;
		int pos = -1;

		while (true) {
			pos = data.find(",", start);	//从0开始找","
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start);
			//cout << tmp << endl;
			v.emplace_back(tmp);
			start = pos + 1;	//因为写文件时, ", "(逗号后面有空格);
		}
		mRecord.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	/*for (auto &x : mRecord) {
		cout << x.first << "号冠军: "
			<< x.second[0] << "分数: "
			<< x.second[1] << endl;
	}*/

	cout << endl;
}

//显示往届得分
void SpeechManager::showRecord() {
	/*
	1002,86.675,1009,81.3,1007,78.55,
	1002,86.675,1009,81.3,1007,78.55,
	*/
	//往届记录
	//map<int, vector<string>> mRecord;
	if (this->fileIsEmpty) {
		cout << "文件不存在或文件为空\n";
		return;
	}

	for (auto x : mRecord) {
		cout << x.first << "届: "
			<< "冠军:" << x.second[0] << " 分数:" << x.second[1] << ", "
			<< "亚军:" << x.second[2] << " 分数:" << x.second[3] << ", "
			<< "季军:" << x.second[4] << " 分数:" << x.second[5] << "\n";
	}
	cout << endl;
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord() {
	cout << "确认清空?(y/n)\n";

	char ch = 0;
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {

		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();

		cout << "清空完成\n";

	}
	system("pause");
	system("cls");
}