#pragma once
#include "Singleton.h"


class ShareDataManager : public Singleton<ShareDataManager> {

	friend Singleton<ShareDataManager>;

private:
	int score;		//今回のスコア
	int highscore;	//ハイスコア

private:
	ShareDataManager();
	~ShareDataManager() = default;

public:
	void initialize();	//初期化

};







