#include "Equipment.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_name">名前</param>
/// <param name="_level">レベル</param>
/// <param name="_part_type">装備部位</param>
/// <param name="_parameter">パラメータ</param>
/// <param name="_attribute_power">属性値</param>
Equipment::Equipment(const std::string& _name, const int _level, const PartType _part_type, const EquipParameter& _parameter, const AttributePower& _attribute_power)
	: Item(_name, _level) 
	, partType(_part_type)
	, parameter(_parameter)
	, attributePower(_attribute_power) {
}

/// <summary>
/// 情報の取得
/// </summary>
/// <returns>
/// 情報テキスト
/// </returns>
std::string Equipment::getDetail() const {
	std::string str;
	str = partType.getName() + " : ";
	str += name + "+" + std::to_string(level);
	str += " " + attributePower.getDetail();
	return str;
}

/// <summary>
/// パラメータの取得
/// </summary>
/// <returns>
/// パラメータ
/// </returns>
const EquipParameter& Equipment::getParameter() const {
	return parameter;
}

/// <summary>
/// 装備部位の取得
/// </summary>
/// <returns>
/// 装備部位
/// </returns>
const PartType Equipment::getPartType() const {
	return partType;
}
