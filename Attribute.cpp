#include "Attribute.h"
#include "ErrorMessage.h"
#include <iostream>



AttributePower::AttributePower(const Attribute _attribute, const int _power)
	: attribute(_attribute)
	, power(_power) {
}

std::string AttributePower::getDetail() const {
	std::string str = "";
	switch (attribute) {
	case Attribute::Fire:   str.append("�� "); break;
	case Attribute::Freeze: str.append("�X "); break;
	case Attribute::Wind:   str.append("�� "); break;
	default:				ErrorMessage("�����f�[�^�̑������s���ł�"); break;
	}
	str.append(std::to_string(power));

	return str;
}
