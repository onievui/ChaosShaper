#include "ItemFactory.h"
#include "Equipment.h"
#include "Character.h"
#include "RandMt.h"
#include "ErrorMessage.h"


/// <summary>
/// アイテムの生成
/// </summary>
/// <param name="_floor">階層</param>
/// <returns>
/// アイテム
/// </returns>
std::vector<std::unique_ptr<Item>> ItemFactory::createItems(const int _floor) {
	std::vector<std::unique_ptr<Item>> items;
	int get_items_num = (std::min)(RandMt::GetRand(2) + _floor / 5 + 2, Character::ITEMS_MAX);
	for (int i = 0; i < get_items_num; ++i) {
		PartType part_type = (PartType)RandMt::GetRand((int)PartType::Num);
		int rank = RandMt::GetRand(3);
		//属性の抽選
		Attribute attribute;
		int attribute_seed = RandMt::GetRand(6);
		switch (attribute_seed) {
		case 0:
			attribute = Attribute::Fire;
			break;
		case 1:
			attribute = Attribute::Freeze;
			break;
		case 2:
			attribute = Attribute::Wind;
			break;
		default:
			attribute = Attribute::Normal;
			break;
		}

		//名前の生成
		std::string name = generateName(part_type, rank);

		//パラメータの生成
		EquipParameter parameter = generateParameter(part_type, rank, _floor);

		//属性値の生成
		AttributePower attribute_power = generateAttributePower(attribute, &parameter, part_type);

		items.emplace_back(std::make_unique<Equipment>(name, _floor, part_type, parameter, attribute_power));
	}

	return items;
}

/// <summary>
/// 名前の生成
/// </summary>
/// <param name="_part_type">部位種</param>
/// <param name="_rank">ランク</param>
/// <returns>
/// 名前
/// </returns>
std::string ItemFactory::generateName(const PartType _part_type, const int _rank) {
	static std::string equipment_names[(int)PartType::Num][3] = {
		{"帽子","ヘルメット","兜"},
		{"シャツ","鎖帷子","重鎧"},
		{"木の枝","ナイフ","ブロンズソード"},
		{"靴下","スニーカー","ローラーシューズ"}
	};

	return equipment_names[(int)_part_type][_rank];
}


/// <summary>
/// パラメータの生成
/// </summary>
/// <param name="_part_type">部位種</param>
/// <param name="_rank">ランク</param>
/// <param name="_floor">階層</param>
/// <returns>
/// パラメータ
/// </returns>
EquipParameter ItemFactory::generateParameter(const PartType _part_type, const int _rank, const int _floor) {
	EquipParameter parameter;

	switch (_part_type) {
	case (int)PartType::Head:
		parameter = EquipParameter(0, 2, 0, 4);
		break;
	case (int)PartType::Body:
		parameter = EquipParameter(0, 3, 0, 0);
		break;
	case (int)PartType::Arm:
		parameter = EquipParameter(2, 0, 0, 0);
		break;
	case (int)PartType::Leg:
		parameter = EquipParameter(0, 1, 4, 0);
		break;
	default:
		ErrorMessage("パラメータの生成で不正な値が渡されましたされました");
		break;
	}

	parameter.levelUp(_floor, _rank);

	return parameter;
}

/// <summary>
/// 属性値の生成
/// </summary>
/// <param name="_attribute">属性</param>
/// <param name="_parameter">パラメータ</param>
/// <param name="_part_type">部位種</param>
/// <returns>
/// 属性値
/// </returns>
AttributePower ItemFactory::generateAttributePower(const Attribute _attribute, EquipParameter* _parameter, const PartType _part_type) {
	int power = 0;
	int* relational_param;
	if (_part_type.equal(PartType::Arm)) {
		relational_param = &_parameter->attack;
	}
	else {
		relational_param = &_parameter->defence;
	}
	switch (_attribute) {
	case Attribute::Normal:
		power = 0;
		break;
	case Attribute::Fire:
		power = *relational_param * 2 / 5 + 1;
		break;
	case Attribute::Freeze:
		power = *relational_param * 2 / 5 + 1;
		break;
	case Attribute::Wind:
		power = *relational_param * 2 / 5 + 1;
		break;
	default:
		ErrorMessage("属性値の生成で不正な値が渡されました");
		break;
	}

	if (power != 0) {
		*relational_param /= 2;
	}

	return AttributePower(_attribute, power);
}


