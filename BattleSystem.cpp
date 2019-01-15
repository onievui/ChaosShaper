#include "BattleSystem.h"
#include <vector>


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_player">�v���C���[�ւ̃|�C���^</param>
/// <param name="_enemy">�G�ւ̃|�C���^</param>
BattleSystem::BattleSystem(Player* _player, Enemy* _enemy)
	: player(_player)
	, enemy(_enemy) {
}

/// <summary>
/// �퓬����
/// </summary>
void BattleSystem::battle() {
	CharaParameter player_status = player->getStatus();
	CharaParameter enemy_status = enemy->getStatus();
	CharaParameter* first_chara;
	CharaParameter* next_chara;

	//��U�����߂�
	if (decideFirst(player_status, enemy_status)) {
		first_chara = &player_status;
		next_chara = &enemy_status;
	}
	else {
		first_chara = &enemy_status;
		next_chara = &player_status;
	}

	//�U���f�[�^�̍쐬
	

	//�ǂ��炩��HP�������Ȃ�܂ő�����
	while (player_status.hp > 0 && enemy_status.hp > 0) {
		
	}
}

/// <summary>
/// ��U�����߂�
/// </summary>
/// <param name="_chara1">�L�����N�^�[1�̃p�����[�^</param>
/// <param name="_chara2">�L�����N�^�[2�̃p�����[�^</param>
/// <returns>
/// true : �L�����N�^�[1����U
/// false : �L�����N�^�[2����U
/// </returns>
bool BattleSystem::decideFirst(const CharaParameter& _chara1, const CharaParameter& _chara2) {
	return _chara1.speed >= _chara2.speed;
}
