#include "Equipment.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_name">���O</param>
/// <param name="_level">���x��</param>
/// <param name="_part_type">��������</param>
/// <param name="_parameter">�p�����[�^</param>
/// <param name="_attribute_power">�����l</param>
Equipment::Equipment(const std::string& _name, const int _level, const PartType _part_type, const EquipParameter& _parameter, const AttributePower& _attribute_power)
	: Item(_name, _level) 
	, partType(_part_type)
	, parameter(_parameter)
	, attributePower(_attribute_power) {
}

/// <summary>
/// ���̎擾
/// </summary>
/// <returns>
/// ���e�L�X�g
/// </returns>
std::string Equipment::getDetail() const {
	std::string str;
	str = partType.getName() + " : ";
	str += name + "+" + std::to_string(level);
	std::string attribute_text = attributePower.getDetail();
	if (!attribute_text.empty()) {
		str += attribute_text;
	}
	return str;
}

/// <summary>
/// ���ʂ��܂܂Ȃ����̎擾
/// </summary>
/// <returns>
/// ���e�L�X�g
/// </returns>
std::string Equipment::getDetailNoPart() const {
	std::string str;
	str = name + "+" + std::to_string(level);
	std::string attribute_text = attributePower.getDetail();
	if (!attribute_text.empty()) {
		str += attribute_text;
	}
	return str;
}

/// <summary>
/// �p�����[�^�̎擾
/// </summary>
/// <returns>
/// �p�����[�^
/// </returns>
const EquipParameter& Equipment::getParameter() const {
	return parameter;
}

/// <summary>
/// �������ʂ̎擾
/// </summary>
/// <returns>
/// ��������
/// </returns>
const PartType Equipment::getPartType() const {
	return partType;
}

/// <summary>
/// �����l�̎擾
/// </summary>
/// <returns>
/// �����l
/// </returns>
const AttributePower& Equipment::getAttributePower() const {
	return attributePower;
}
