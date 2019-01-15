#pragma once
#include <string>

/// <summary>
/// ‘•”õ‘®«
/// </summary>
enum class Attribute : int {
	Normal,
	Fire,
	Freeze,
	Wind,
	Num
};


/// <summary>
/// ‘®«‘Š«
/// </summary>
static const int AttributeChemistories[(int)Attribute::Num][(int)Attribute::Num] = {
	{0,0,0,0},
	{0,0,-1,1},
	{0,1,0,-1},
	{0,-1,1,0}
};


/// <summary>
/// ‘®«’lƒNƒ‰ƒX
/// </summary>
class AttributePower {
public:
	Attribute attribute;
	int power;

public:
	AttributePower(const Attribute _attribute, const int _power);

public:
	std::string getDetail() const;	//î•ñ‚Ìæ“¾
};