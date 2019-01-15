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
	//CharaParameter player_status = player->getStatus();
	//CharaParameter enemy_status = enemy->getStatus();
	//CharaParameter* first_chara;
	//CharaParameter* next_chara;
	Character* first_chara;
	Character* next_chara;
	std::vector<AttackParameter> first_attack_parameter;
	std::vector<AttackParameter> next_attack_parameter;

	//先攻を決める
	if (decideFirst(player->getStatus(), enemy->getStatus())) {
		first_chara = player;
		next_chara = enemy;
	}
	else {
		first_chara = enemy;
		next_chara = player;
	}

	//攻撃データの作成
	first_attack_parameter = createAttackParameters(first_chara);
	next_attack_parameter = createAttackParameters(next_chara);
	
	//防御データの作成


	//どちらかのHPが無くなるまで続ける
	while (player->getDefaultStatus().hp > 0 && enemy->getDefaultStatus().hp > 0) {
		
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

/// <summary>
/// 攻撃パラメータの作成
/// </summary>
/// <param name="_chara">キャラクター</param>
/// <returns>
/// 攻撃パラメータ
/// </returns>
std::vector<AttackParameter> BattleSystem::createAttackParameters(Character* _chara) {
	//攻撃パラメータ
	std::vector<AttackParameter> attackParameters;
	//キャラクターの元の能力
	int chara_attack = _chara->getDefaultStatus().attack;
	int chara_critical = _chara->getDefaultStatus().critical;
	//防具で追加された能力
	int add_attack = 0;
	int add_critical = 0;
	for (const auto& part : _chara->getParts()) {
		//腕以外の場合
		if (!part->getPartType().equal(part->getPartType())) {
			//装備していないなら飛ばす
			if (!part->isEquipping()) {
				continue;
			}
			//全攻撃共通のパラメータに加える
			add_attack += part->getEquipment()->getParameter().attack;
			add_critical += part->getEquipment()->getParameter().critical;
		}
		//腕の場合
		else {
			//パラメータを追加する
			attackParameters.emplace_back(AttackParameter(chara_attack, chara_critical, part.get()));
		}
	}

	//攻撃部位がない場合用の攻撃パラメータ
	if (attackParameters.empty()) {
		attackParameters.emplace_back(AttackParameter(chara_attack, chara_critical));
	}

	//全攻撃共通のパラメータを加える
	for (auto& attack_parameter : attackParameters) {
		attack_parameter.attack += add_attack;
		attack_parameter.critical += add_critical;
	}

	return attackParameters;
}
