#include "BattleSystem.h"
#include <vector>


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_player">プレイヤーへのポインタ</param>
/// <param name="_enemy">敵へのポインタ</param>
BattleSystem::BattleSystem(Player* _player, Enemy* _enemy)
	: player(_player)
	, enemy(_enemy) {
}

/// <summary>
/// 戦闘処理
/// </summary>
void BattleSystem::battle() {
	CharaParameter player_status = player->getStatus();
	CharaParameter enemy_status = enemy->getStatus();
	CharaParameter* first_chara;
	CharaParameter* next_chara;

	//先攻を決める
	if (decideFirst(player_status, enemy_status)) {
		first_chara = &player_status;
		next_chara = &enemy_status;
	}
	else {
		first_chara = &enemy_status;
		next_chara = &player_status;
	}

	//攻撃データの作成
	

	//どちらかのHPが無くなるまで続ける
	while (player_status.hp > 0 && enemy_status.hp > 0) {
		
	}
}

/// <summary>
/// 先攻を決める
/// </summary>
/// <param name="_chara1">キャラクター1のパラメータ</param>
/// <param name="_chara2">キャラクター2のパラメータ</param>
/// <returns>
/// true : キャラクター1が先攻
/// false : キャラクター2が先攻
/// </returns>
bool BattleSystem::decideFirst(const CharaParameter& _chara1, const CharaParameter& _chara2) {
	return _chara1.speed >= _chara2.speed;
}
