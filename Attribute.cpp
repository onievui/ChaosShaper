#include "Attribute.h"
#include <iostream>


AttributePower::AttributePower(const Attribute _attribute, const int _power)
	: attribute(_attribute)
	, power(_power) {
}

std::string AttributePower::getDetail() {
	std::string str = "";
	switch (attribute) {
	case Attribute::Fire:   str.append("炎 "); break;
	case Attribute::Freeze: str.append("氷 "); break;
	case Attribute::Wind:   str.append("風 "); break;
	default:
		std::cout << "属性データの属性が不正です" << std::endl;
		break;
	}
	str.append(std::to_string(power));

	return str;
}
