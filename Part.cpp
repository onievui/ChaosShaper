#include "Part.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_part_type">部位種類</param>
/// <param name="_level">レベル</param>
Part::Part(const PartType _part_type, const int _level)
	: partType(_part_type)
	, level(_level)
	, equipment() {

}

/// <summary>
/// デストラクタ
/// </summary>
Part::~Part() {

}

/// <summary>
/// 情報の取得
/// </summary>
/// <returns>
/// 情報テキスト
/// </returns>
std::string Part::getDetail() const {
	std::string str;
	str = partType.getName() + "+" + std::to_string(level) + " ";
	if (isEquipping()) {
		return str + equipment->getDetailNoPart();
	}
	return str + ": none";
}

/// <summary>
/// レベルの取得
/// </summary>
/// <returns>
/// レベル
/// </returns>
int Part::getLevel() const {
	return level;
}

/// <summary>
/// 部位種類の取得
/// </summary>
/// <returns></returns>
PartType Part::getPartType() const {
	return partType;
}

/// <summary>
/// 装備中かどうか
/// </summary>
/// <returns>
/// true : 装備中
/// false : 装備していない
/// </returns>
bool Part::isEquipping() const {
	return equipment ? true : false;
}

/// <summary>
/// 装備可能かどうか
/// </summary>
/// <param name="_equipment">装備品</param>
/// <returns>
/// true : 装備可能
/// false : 装備不可
/// </returns>
bool Part::canEquip(const Equipment* _equipment) const {
	return partType.equal(_equipment->getPartType());
}

/// <summary>
/// 装備品の装備
/// </summary>
/// <param name="_equipment">装備品</param>
void Part::setEquipment(std::unique_ptr<Equipment>&& _equipment) {
	if (partType.equal(_equipment->getPartType())) {
		equipment = std::move(_equipment);
	}
}

/// <summary>
/// 装備品の取得
/// </summary>
/// <returns>
/// 装備品
/// </returns>
Equipment* Part::getEquipment() const {
	if (isEquipping()) {
		return equipment.get();
	}
	return nullptr;
}

/// <summary>
/// 装備品の解除
/// </summary>
/// <returns>
/// 装備品
/// </returns>
std::unique_ptr<Equipment> Part::removeEquipment() {
	std::unique_ptr<Equipment> equip = std::move(equipment);
	equipment.reset(nullptr);
	return std::move(equip);
}
