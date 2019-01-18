#include "EnemyFactory.h"
#include "ItemFactory.h"
#include "ErrorMessage.h"
#include "RandMt.h"
#include <algorithm>



/// <summary>
/// 敵生成処理
/// </summary>
/// <param name="_floor">階層</param>
/// <returns>
/// 敵
/// </returns>
std::unique_ptr<Enemy> EnemyFactory::createEnemy(const int _floor) {
	//ランクの生成
	int rank = RandMt::GetRand(_floor / 10 + 1);

	//名前の生成
	EnemyID enemy_id = (EnemyID)RandMt::GetRand((std::min)(_floor / 6 + 2, (int)EnemyID::Num));
	auto enemy = std::make_unique<Enemy>(generateName(enemy_id, rank));

	//パラメータの生成
	enemy->setStatus(generateParameter(enemy_id, rank, _floor));

	//部位の生成
	enemy->addParts(generateParts(_floor));

	//装備の生成
	enemy->addItems(ItemFactory::createItems(_floor));

	//自動装備
	enemy->autoEquipping();

	return enemy;
}

/// <summary>
/// 名前の生成
/// </summary>
/// <param name="_enemy_id">敵ID</param>
/// <param name="_rank">ランク</param>
/// <returns>
/// 名前
/// </returns>
std::string EnemyFactory::generateName(const EnemyID _enemy_id, const int _rank) {
	std::string name;
	
	switch (_enemy_id) {
	case EnemyID::Slime:
		name.append("スライム");
		break;
	case EnemyID::Goblin:
		name.append("ゴブリン");
		break;
	case EnemyID::Ghost:
		name.append("ゴースト");
		break;
	case EnemyID::Man:
		name.append("おじさん");
		break;
	case EnemyID::Dragon:
		name.append("ドラゴン");
		break;
	default:
		ErrorMessage("名前の生成で不正な値が渡されましたされました");
		break;
	}

	return name;
}

/// <summary>
/// パラメータの生成
/// </summary>
/// <param name="_enemy_id">敵ID</param>
/// <param name="_rank">ランク</param>
/// <param name="_floor">階層</param>
/// <returns>
/// パラメータ
/// </returns>
CharaParameter EnemyFactory::generateParameter(const EnemyID _enemy_id, const int _rank, const int _floor) {

	CharaParameter parameter;

	switch (_enemy_id) {
	case EnemyID::Slime:
		parameter = CharaParameter(_floor, 10, 2, 2, 2, 0);
		break;
	case EnemyID::Goblin:
		parameter = CharaParameter(_floor, 15, 3, 3, 3, 3);
		break;
	case EnemyID::Ghost:
		parameter = CharaParameter(_floor, 13, 3, 2, 5, 2);
		break;
	case EnemyID::Man:
		parameter = CharaParameter(_floor, 20, 4, 4, 4, 3);
		break;
	case EnemyID::Dragon:
		parameter = CharaParameter(_floor, 30, 6, 6, 6, 5);
		break;
	default:
		ErrorMessage("パラメータの生成で不正な値が渡されましたされました");
		break;
	}

	parameter.levelUp(_floor - 1);

	return parameter;
}

/// <summary>
/// 部位の生成
/// </summary>
/// <param name="_floor">階層</param>
/// <returns>
/// 部位
/// </returns>
std::vector<std::unique_ptr<Part>> EnemyFactory::generateParts(const int _floor) {
	std::vector<std::unique_ptr<Part>> parts;
	int get_parts_num = (std::min)(RandMt::GetRand(2) + _floor / 6, Character::PARTS_MAX);
	for (int i = 0; i < get_parts_num; ++i) {
		PartType part_type = (PartType)RandMt::GetRand(PartType::Num.getData());
		parts.emplace_back(std::make_unique<Part>(part_type, _floor));
	}

	return parts;
}
