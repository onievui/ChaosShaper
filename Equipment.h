#pragma once
#include "Item.h"
#include "Parameter.h"
#include "Attribute.h"
#include "PartType.h"


/// <summary>
/// ‘•”õ•iƒNƒ‰ƒX
/// </summary>
class Equipment : public Item {
private:
	PartType partType;
	EquipParameter parameter;
	AttributePower attributePower;

public:
	Equipment(const std::string& _name, const int _level, const PartType _part_type, const EquipParameter& _parameter, const AttributePower& _attribute_power);
	virtual ~Equipment() = default;

public:
	std::string getDetail() const override;
	std::string getDetailNoPart() const;
	const EquipParameter& getParameter() const;
	const PartType getPartType() const;
	const AttributePower& getAttributePower() const;
};

