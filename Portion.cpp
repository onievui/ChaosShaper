#include "Portion.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_name">名前</param>
/// <param name="_level">レベル</param>
/// <param name="_power">強度</param>
Portion::Portion(const std::string& _name, const int _level, const int _power)
	: Item(_name, _level) 
	, power(_power) {
}

/// <summary>
/// 情報の取得
/// </summary>
/// <returns>
/// 情報テキスト
/// </returns>
std::string Portion::getDetail() const {
	std::string str;
	str = name + "+" + std::to_string(level);
	return str;
}
