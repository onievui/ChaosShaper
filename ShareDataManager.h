#pragma once
#include "Singleton.h"
#include <string>

class ShareDataManager : public Singleton<ShareDataManager> {

	friend Singleton<ShareDataManager>;

private:
	int finalFloor;
	std::string playerName;
	std::string enemyName;

private:
	ShareDataManager();
	~ShareDataManager() = default;

public:
	void initialize();	//‰Šú‰»
	void saveData(const int _floor, const std::string& _player_name, const std::string& _enemy_name);
	int getFloor();
	std::string getPlayerName();
	std::string getEnemyName();
};







