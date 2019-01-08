#include "Equipment.h"



Equipment::Equipment(const std::string& _name, const int _level, const PartType _part_type, const EquipParameter& _parameter, const AttributePower& _attribute_power)
	: Item(_name, _level) 
	, partType(_part_type)
	, parameter(_parameter)
	, attributePower(_attribute_power) {
}

std::string Equipment::getDetail() const {
	std::string str;
	str = partType.getName() + " : ";
	str += name + "+" + std::to_string(level);
	str += " " + attributePower.getDetail();
	return str;
}

const EquipParameter& Equipment::getParameter() const {
	return parameter;
}

const PartType Equipment::getPartType() const {
	return partType;
}
