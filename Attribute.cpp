#include "Attribute.h"
#include "ErrorMessage.h"
#include <iostream>


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_attribute">属性</param>
/// <param name="_power">強度</param>
AttributePower::AttributePower(const Attribute _attribute, const int _power)
	: attribute(_attribute)
	, power(_power) {
}

/// <summary>
/// 情報の取得
/// </summary>
/// <returns>
/// 情報テキスト
/// </returns>
std::string AttributePower::getDetail() const {
	std::string str = "";
	switch (attribute) {
	case Attribute::Fire:   str.append("炎 "); break;
	case Attribute::Freeze: str.append("氷 "); break;
	case Attribute::Wind:   str.append("風 "); break;
	default:				ErrorMessage("属性データの属性が不正です"); break;
	}
	str.append(std::to_string(power));

	return str;
}
