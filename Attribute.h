#pragma once
#include <string>

/// <summary>
/// 装備属性
/// </summary>
enum class Attribute : int {
	Normal,
	Fire,
	Freeze,
	Wind,
	Num
};


/// <summary>
/// 属性相性
/// </summary>
static const int AttributeChemistories[(int)Attribute::Num][(int)Attribute::Num] = {
	{0,0,0,0},
	{0,0,-1,1},
	{0,1,0,-1},
	{0,-1,1,0}
};


/// <summary>
/// 属性値クラス
/// </summary>
class AttributePower {
public:
	Attribute attribute;
	int power;

public:
	AttributePower(const Attribute _attribute, const int _power);

public:
	std::string getDetail() const;	//情報の取得
};