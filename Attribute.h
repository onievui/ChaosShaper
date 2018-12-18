#pragma once
#include <string>


enum class Attribute : int {
	Fire,
	Freeze,
	Wind,
	Num
};


class AttributePower {
public:
	Attribute attribute;
	int power;

public:
	AttributePower(const Attribute _attribute, const int _power);

public:
	std::string getDetail();
};