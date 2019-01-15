#include "Item.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_name">名前</param>
/// <param name="_level">レベル</param>
Item::Item(const std::string& _name, const int _level)
	: name(_name)
	, level(_level) {
}

/// <summary>
/// 名前の取得
/// </summary>
/// <returns>
/// 名前
/// </returns>
const std::string& Item::getName() const {
	return name;
}

/// <summary>
/// 情報の取得
/// </summary>
/// <returns>
/// 情報テキスト
/// </returns>
std::string Item::getDetail() const {
	std::string str;
	str = name + "+" + std::to_string(level);
	return str;
}

/// <summary>
/// レベルの取得
/// </summary>
/// <returns>
/// レベル
/// </returns>
int Item::getLevel() const {
	return level;
}
