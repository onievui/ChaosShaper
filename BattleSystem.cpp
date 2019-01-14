#include "BattleSystem.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_player">プレイヤーへのポインタ</param>
/// <param name="_enemy">敵へのポインタ</param>
BattleSystem::BattleSystem(Player* _player, Enemy* _enemy)
	: player(_player)
	, enemy(_enemy) {
}

void BattleSystem::battle()
{
}
