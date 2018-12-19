#include "Equipment.h"



Equipment::Equipment(const std::string& _name, const int _level, const PartType _part_type, const CharaParameter& _parameter, const AttributePower& _attribute_power)
	: Item(_name, _level) 
	, partType(_part_type)
	, parameter(_parameter)
	, attributePower(_attribute_power) {
}

std::string Equipment::getDetail() {
	std::string str;
	str = PartTypeFunc::getPartTypeName(partType) + " ";
	str += name + "+" + std::to_string(level);
	str += " " + attributePower.getDetail();
	return str;
}
