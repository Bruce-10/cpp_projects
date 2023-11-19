#include "speechManager.h"


SpeechManager::SpeechManager() {
	//��ʼ����Ա����
	this->initSpeech();

	//��������ѡ��
	this->createSpeaker();

	//��ȡ�����¼
	this->loadRecord();
}

SpeechManager::~SpeechManager() {

}

//��ʾ�˵�
void SpeechManager::showMenu() {
	cout << "**************************************\n"; 
	cout << "*********** ��ӭ�μ��ݽ����� ********\n";
	cout << "*********** 1. ��ʼ�ݽ����� ********\n";
	cout << "*********** 2. �鿴�����¼ ********\n";
	cout << "*********** 3. ��ձ�����¼ ********\n";
	cout << "*********** 0. �˳��������� ********\n";
	cout << "**************************************\n";
	cout << endl;
}

//��ʼ����Ա����
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->mSpeaker.clear();
	this->mIndex = 1;
	this->mRecord.clear();
}

//����ѡ��
void SpeechManager::createSpeaker() {
	string str = "ABCDEFGHIJKL";
	//����12��ѡ��
	for (int i = 0; i < str.size(); i++) {
		string _name = "ѡ��";
		_name += str[i];

		Speaker sp;
		sp.mName = _name;
		sp.mScore[0] = 0;
		sp.mScore[1] = 0;

		this->v1.emplace_back(1001 + i);
		this->mSpeaker.insert(make_pair(1001 + i, sp));
	}
	//����, ���, �÷�
}

//�������̵ĺ���
void SpeechManager::startSpeech() {
	
	//��һ�ֱ���
	//1.��ǩ
	this->speechDraw();

	//2. ����
	this->speechContest();

	//3. ��ʾ�������
	this->showScore();

	//if mIndex = 2, �����
	if (mIndex == 2) {
		//�������:
		this->saveRecord();
		cout << "����������\n";

//
		//��ʼ����Ա����
		this->initSpeech();

		//��������ѡ��
		this->createSpeaker();

		//��ȡ�����¼
		this->loadRecord();
// //���⼸�д�����Ϊ�˸��±������������, ����鿴���������¼��bug

		system("pause");
		system("cls");
		return;
	}

	//�ڶ��ֱ���
	this->mIndex++;
	startSpeech();
}

//��ǩ
void SpeechManager::speechDraw() {
	cout << "��<< " << mIndex << " >>��ѡ�����ڳ�ǩ\n";
	if (mIndex == 1) {
		//�Ե�һ�ֵı�����ϴ��
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

//����
void SpeechManager::speechContest() {
	cout << "��  " << this->mIndex << " �ֱ���\n";
	//����Ԫ�ض������Ԫ�ص�** ��ֵ** �Զ�����,  ����doubleҪ��ǰ
	multimap< double, int, greater<double>> groupScore;	//greaterΪ����

	vector<int> v_src; //������Ա������

	int num = 0;
	mIndex == 1 ? v_src = this->v1 : v_src = this->v2;

	for (auto x : v_src) {
		num++;
		multiset<double> dqe;
		//10����ί���
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
			dqe.insert(score);
		}
		//����ƽ����
		dqe.erase(dqe.begin());
		dqe.erase(--dqe.end());

		//�����ܺ�:`accumulate(iterator beg, iterator end, value);  `
		double sum = accumulate(dqe.begin(), dqe.end(), 0.0f);
		double avg = sum / 8;

		//ÿ����ƽ����
		//cout << "��ţ� " << x  << " ѡ�֣� " << this->mSpeaker[x].mName << " ��ȡƽ����Ϊ�� " << avg << endl;  //��ӡ����
		this->mSpeaker[x].mScore[this->mIndex - 1] = avg;

		groupScore.insert(make_pair( avg, x));

		if (num % 6 == 0) { //���������һ��
			cout << "�� " << num / 6 << "С��ɼ�:\n";
			for (auto mp : groupScore) {
				cout << "��ţ� " << mp.second
					<< " ѡ�֣� " << this->mSpeaker[mp.second].mName 
					<< " ��Ϊ�� " << mp.first << endl;  //��ӡ����
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
	cout << "��  " << this->mIndex << " �ֱ������\n";
	system("pause");
}


//��ʾ�������
void SpeechManager::showScore() {
	cout << "��  " << this->mIndex << " �ֱ��������������\n";

	//��ʱ��������ѡ�ֱ��:
	vector<int> v_src;
	v_src = this->mIndex == 1 ? v2 : vVictory;

	//��mSpeaker[v_src[i]].secore��������
	multimap< double, int, greater<double>> groupScore;	//greaterΪ����
	for (auto x : v_src) {
		groupScore.insert(make_pair(this->mSpeaker[x].mScore[mIndex - 1], x));
	}

	//����v_src����, ��ӡ�������
	for (auto mp : groupScore) {
		cout << "��ţ� " << mp.second
			<< " ѡ�֣� " << this->mSpeaker[mp.second].mName
			<< " ��Ϊ�� " << mp.first << endl;  //��ӡ����
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

//�����¼
void SpeechManager::saveRecord() {
	/*
	ios::outΪд�ļ������ļ�
	ios::app׷�ӷ�ʽд�ļ�
	*/
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	//��ÿ���˵ĳɼ�д���ļ���
	for (auto x : vVictory) {
		//ofs << x <<"," << this->mSpeaker[x].mScore[1] << "," << endl;
		ofs << x <<"," << this->mSpeaker[x].mScore[1] << ",";
	}
	ofs << endl;

	ofs.close();

	cout << "��¼�Ѿ�����\n";
	this->fileIsEmpty = false;
}

//��ȡ��¼
void SpeechManager::loadRecord() {
	//ios::inΪ���ļ������ļ�
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�������\n";
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;	//�ȶ�ȡһ���ַ�, �ж��Ƿ�Ϊ��
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�����, ��Ϊ��\n";
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch); //���ոն�ȡ���ַ��ڷŻ�ȥ, ��֤�ַ���������

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
			pos = data.find(",", start);	//��0��ʼ��","
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start);
			//cout << tmp << endl;
			v.emplace_back(tmp);
			start = pos + 1;	//��Ϊд�ļ�ʱ, ", "(���ź����пո�);
		}
		mRecord.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	/*for (auto &x : mRecord) {
		cout << x.first << "�Źھ�: "
			<< x.second[0] << "����: "
			<< x.second[1] << endl;
	}*/

	cout << endl;
}

//��ʾ����÷�
void SpeechManager::showRecord() {
	/*
	1002,86.675,1009,81.3,1007,78.55,
	1002,86.675,1009,81.3,1007,78.55,
	*/
	//�����¼
	//map<int, vector<string>> mRecord;
	if (this->fileIsEmpty) {
		cout << "�ļ������ڻ��ļ�Ϊ��\n";
		return;
	}

	for (auto x : mRecord) {
		cout << x.first << "��: "
			<< "�ھ�:" << x.second[0] << " ����:" << x.second[1] << ", "
			<< "�Ǿ�:" << x.second[2] << " ����:" << x.second[3] << ", "
			<< "����:" << x.second[4] << " ����:" << x.second[5] << "\n";
	}
	cout << endl;
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord() {
	cout << "ȷ�����?(y/n)\n";

	char ch = 0;
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {

		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������
		this->initSpeech();

		//����ѡ��
		this->createSpeaker();

		//��ȡ�����¼
		this->loadRecord();

		cout << "������\n";

	}
	system("pause");
	system("cls");
}