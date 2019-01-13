#include "Attribute.h"
#include "ErrorMessage.h"
#include <iostream>


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_attribute">����</param>
/// <param name="_power">���x</param>
AttributePower::AttributePower(const Attribute _attribute, const int _power)
	: attribute(_attribute)
	, power(_power) {
}

/// <summary>
/// ���̎擾
/// </summary>
/// <returns>
/// ���e�L�X�g
/// </returns>
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
