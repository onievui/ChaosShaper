#include "ShareDataManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
ShareDataManager::ShareDataManager() {
	initialize();
}

/// <summary>
/// �f�[�^�̏�����
/// </summary>
void ShareDataManager::initialize() {
	finalFloor = 0;
	playerName.clear();
	enemyName.clear();
}

/// <summary>
/// �f�[�^�̕ۑ�
/// </summary>
/// <param name="_floor">�K�w</param>
/// <param name="_player_name">�v���C���[��</param>
/// <param name="_enemy_name">�G��</param>
void ShareDataManager::saveData(const int _floor, const std::string & _player_name, const std::string & _enemy_name) {
	finalFloor = _floor;
	playerName = _player_name;
	enemyName = _enemy_name;
}

/// <summary>
/// �K�w�̎擾
/// </summary>
/// <returns>
/// �K�w
/// </returns>
int ShareDataManager::getFloor() {
	return finalFloor;
}

/// <summary>
/// �v���C���[���̎擾
/// </summary>
/// <returns>
/// �v���C���[��
/// </returns>
std::string ShareDataManager::getPlayerName() {
	return playerName;
}

/// <summary>
/// �G���̎擾
/// </summary>
/// <returns>
/// �G��
/// </returns>
std::string ShareDataManager::getEnemyName() {
	return enemyName;
}

