#include "ShareDataManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
ShareDataManager::ShareDataManager() {
	initialize();
}

/// <summary>
/// データの初期化
/// </summary>
void ShareDataManager::initialize() {
	finalFloor = 0;
	playerName.clear();
	enemyName.clear();
}

/// <summary>
/// データの保存
/// </summary>
/// <param name="_floor">階層</param>
/// <param name="_player_name">プレイヤー名</param>
/// <param name="_enemy_name">敵名</param>
void ShareDataManager::saveData(const int _floor, const std::string & _player_name, const std::string & _enemy_name) {
	finalFloor = _floor;
	playerName = _player_name;
	enemyName = _enemy_name;
}

/// <summary>
/// 階層の取得
/// </summary>
/// <returns>
/// 階層
/// </returns>
int ShareDataManager::getFloor() {
	return finalFloor;
}

/// <summary>
/// プレイヤー名の取得
/// </summary>
/// <returns>
/// プレイヤー名
/// </returns>
std::string ShareDataManager::getPlayerName() {
	return playerName;
}

/// <summary>
/// 敵名の取得
/// </summary>
/// <returns>
/// 敵名
/// </returns>
std::string ShareDataManager::getEnemyName() {
	return enemyName;
}

