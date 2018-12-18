#include "Equipment.h"



Equipment::Equipment(const std::string& _name, const int _level, const CharaParameter& _parameter, const AttributePower& _attribute_power)
	: Item(_name, _level) 
	, parameter(_parameter)
	, attributePower(_attribute_power) {
}
