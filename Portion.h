#pragma once
#include "Item.h"


class Portion : public Item {
private:
	int power;
public:
	Portion(const std::string& _name, const int _level, const int _power);
	virtual ~Portion() = default;
};

