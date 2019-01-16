#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>


/// <summary>
/// í“¬ˆ—ƒNƒ‰ƒX
/// </summary>
class BattleSystem {
private:
	Player* player;
	Enemy* enemy;

public:
	BattleSystem(Player* _player, Enemy* _enemy);
	~BattleSystem() = default;
	
public:
	bool battle();

private:
	bool decideFirst(const CharaParameter& _chara1, const CharaParameter& _chara2);
	std::vector<AttackParameter> createAttackParameters(Character* _chara);
	bool dodge(const CharaParameter& _chara1, const CharaParameter& _chara2);
	int attack(const std::vector<AttackParameter>& _attack_parameters, const DefenceParameter& _defence_parameter);
};