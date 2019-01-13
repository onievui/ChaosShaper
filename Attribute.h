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