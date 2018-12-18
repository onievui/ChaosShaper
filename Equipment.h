#pragma once
#include "Item.h"
#include "Parameter.h"
#include "Attribute.h"
#include "PartType.h"


class Equipment : public Item {
private:
	PartType partType;
	CharaParameter parameter;
	AttributePower attributePower;
public:
	Equipment(const std::string& _name, const int _level, const PartType _part_ype, const CharaParameter& _parameter, const AttributePower& _attribute_power);
	virtual ~Equipment() = default;

public:
	std::string getDetail() override;
};

