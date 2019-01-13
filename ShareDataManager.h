#pragma once
#include "Singleton.h"


class ShareDataManager : public Singleton<ShareDataManager> {

	friend Singleton<ShareDataManager>;

private:
	int score;		//����̃X�R�A
	int highscore;	//�n�C�X�R�A

private:
	ShareDataManager();
	~ShareDataManager() = default;

public:
	void initialize();	//������

};







