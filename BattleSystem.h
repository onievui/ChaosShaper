#pragma once
#include "Player.h"
#include "Enemy.h"


class BattleSystem {
private:
	Player* player;
	Enemy* enemy;

public:
	BattleSystem(Player* _player, Enemy* _enemy);
	~BattleSystem() = default;
	
public:
	void battle();

private:
	bool decideFirst(const CharaParameter& _chara1, const CharaParameter& _chara2);
};