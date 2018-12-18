#pragma once
#include "Item.h"
#include "CharaParameter.h"
#include "Attribute.h"


class Equipment : public Item {
private:
	CharaParameter parameter;
	AttributePower attributePower;
public:
	Equipment(const std::string& _name, const int _level, const CharaParameter& _parameter, const AttributePower& _attribute_power);
	virtual ~Equipment() = default;
};

