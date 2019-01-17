#pragma once
#include "Enemy.h"
#include "Parameter.h"
#include <memory>


enum class EnemyID {
	Slime,
	Goblin,
	Ghost,
	Man,
	Dragon,
	Num
};

/// <summary>
/// “G¶¬ƒNƒ‰ƒX
/// </summary>
class EnemyFactory {
public:
	static std::unique_ptr<Enemy> createEnemy(const int _floor);

private:
	static std::string generateName(const EnemyID _enemy_id, const int _rank);
	static CharaParameter generateParameter(const EnemyID _enemy_id, const int _rank, const int _floor);
	static std::vector<std::unique_ptr<Part>> generateParts(const int _floor);
};