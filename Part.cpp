#include "Part.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_part_type">���ʎ��</param>
/// <param name="_level">���x��</param>
Part::Part(const PartType _part_type, const int _level)
	: partType(_part_type)
	, level(_level)
	, equipment() {

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Part::~Part() {

}

/// <summary>
/// ���̎擾
/// </summary>
/// <returns>
/// ���e�L�X�g
/// </returns>
std::string Part::getDetail() const {
	std::string str;
	str = partType.getName() + "+" + std::to_string(level) + " ";
	if (isEquipping()) {
		return str + equipment->getDetailNoPart();
	}
	return str + ": none";
}

/// <summary>
/// ���x���̎擾
/// </summary>
/// <returns>
/// ���x��
/// </returns>
int Part::getLevel() const {
	return level;
}

/// <summary>
/// ���ʎ�ނ̎擾
/// </summary>
/// <returns></returns>
PartType Part::getPartType() const {
	return partType;
}

/// <summary>
/// ���������ǂ���
/// </summary>
/// <returns>
/// true : ������
/// false : �������Ă��Ȃ�
/// </returns>
bool Part::isEquipping() const {
	return equipment ? true : false;
}

/// <summary>
/// �����\���ǂ���
/// </summary>
/// <param name="_equipment">�����i</param>
/// <returns>
/// true : �����\
/// false : �����s��
/// </returns>
bool Part::canEquip(const Equipment* _equipment) const {
	return partType.equal(_equipment->getPartType());
}

/// <summary>
/// �����i�̑���
/// </summary>
/// <param name="_equipment">�����i</param>
void Part::setEquipment(std::unique_ptr<Equipment>&& _equipment) {
	if (partType.equal(_equipment->getPartType())) {
		equipment = std::move(_equipment);
	}
}

/// <summary>
/// �����i�̎擾
/// </summary>
/// <returns>
/// �����i
/// </returns>
Equipment* Part::getEquipment() const {
	if (isEquipping()) {
		return equipment.get();
	}
	return nullptr;
}

/// <summary>
/// �����i�̉���
/// </summary>
/// <returns>
/// �����i
/// </returns>
std::unique_ptr<Equipment> Part::removeEquipment() {
	std::unique_ptr<Equipment> equip = std::move(equipment);
	equipment.reset(nullptr);
	return std::move(equip);
}
