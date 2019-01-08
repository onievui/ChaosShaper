#include "Portion.h"


Portion::Portion(const std::string& _name, const int _level, const int _power)
	: Item(_name, _level) 
	, power(_power) {
}

std::string Portion::getDetail() const {
	std::string str;
	str = name + "+" + std::to_string(level);
	return str;
}
