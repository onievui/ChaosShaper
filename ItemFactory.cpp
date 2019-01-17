#include "ItemFactory.h"
#include "Equipment.h"
#include "Character.h"
#include "RandMt.h"
#include "ErrorMessage.h"


/// <summary>
/// �A�C�e���̐���
/// </summary>
/// <param name="_floor">�K�w</param>
/// <returns>
/// �A�C�e��
/// </returns>
std::vector<std::unique_ptr<Item>> ItemFactory::createItems(const int _floor) {
	std::vector<std::unique_ptr<Item>> items;
	int get_items_num = (std::min)(RandMt::GetRand(2) + _floor / 5 + 2, Character::ITEMS_MAX);
	for (int i = 0; i < get_items_num; ++i) {
		PartType part_type = (PartType)RandMt::GetRand((int)PartType::Num);
		int rank = RandMt::GetRand(3);
		//�����̒��I
		Attribute attribute;
		int attribute_seed = RandMt::GetRand(6);
		switch (attribute_seed) {
		case 0:
			attribute = Attribute::Fire;
			break;
		case 1:
			attribute = Attribute::Freeze;
			break;
		case 2:
			attribute = Attribute::Wind;
			break;
		default:
			attribute = Attribute::Normal;
			break;
		}

		//���O�̐���
		std::string name = generateName(part_type, rank);

		//�p�����[�^�̐���
		EquipParameter parameter = generateParameter(part_type, rank, _floor);

		//�����l�̐���
		AttributePower attribute_power = generateAttributePower(attribute, &parameter, part_type);

		items.emplace_back(std::make_unique<Equipment>(name, _floor, part_type, parameter, attribute_power));
	}

	return items;
}

/// <summary>
/// ���O�̐���
/// </summary>
/// <param name="_part_type">���ʎ�</param>
/// <param name="_rank">�����N</param>
/// <returns>
/// ���O
/// </returns>
std::string ItemFactory::generateName(const PartType _part_type, const int _rank) {
	static std::string equipment_names[(int)PartType::Num][3] = {
		{"�X�q","�w�����b�g","��"},
		{"�V���c","����q","�d�Z"},
		{"�؂̎}","�i�C�t","�u�����Y�\�[�h"},
		{"�C��","�X�j�[�J�[","���[���[�V���[�Y"}
	};

	return equipment_names[(int)_part_type][_rank];
}


/// <summary>
/// �p�����[�^�̐���
/// </summary>
/// <param name="_part_type">���ʎ�</param>
/// <param name="_rank">�����N</param>
/// <param name="_floor">�K�w</param>
/// <returns>
/// �p�����[�^
/// </returns>
EquipParameter ItemFactory::generateParameter(const PartType _part_type, const int _rank, const int _floor) {
	EquipParameter parameter;

	switch (_part_type) {
	case (int)PartType::Head:
		parameter = EquipParameter(0, 2, 0, 4);
		break;
	case (int)PartType::Body:
		parameter = EquipParameter(0, 3, 0, 0);
		break;
	case (int)PartType::Arm:
		parameter = EquipParameter(2, 0, 0, 0);
		break;
	case (int)PartType::Leg:
		parameter = EquipParameter(0, 1, 4, 0);
		break;
	default:
		ErrorMessage("�p�����[�^�̐����ŕs���Ȓl���n����܂�������܂���");
		break;
	}

	parameter.levelUp(_floor, _rank);

	return parameter;
}

/// <summary>
/// �����l�̐���
/// </summary>
/// <param name="_attribute">����</param>
/// <param name="_parameter">�p�����[�^</param>
/// <param name="_part_type">���ʎ�</param>
/// <returns>
/// �����l
/// </returns>
AttributePower ItemFactory::generateAttributePower(const Attribute _attribute, EquipParameter* _parameter, const PartType _part_type) {
	int power = 0;
	int* relational_param;
	if (_part_type.equal(PartType::Arm)) {
		relational_param = &_parameter->attack;
	}
	else {
		relational_param = &_parameter->defence;
	}
	switch (_attribute) {
	case Attribute::Normal:
		power = 0;
		break;
	case Attribute::Fire:
		power = *relational_param * 2 / 5 + 1;
		break;
	case Attribute::Freeze:
		power = *relational_param * 2 / 5 + 1;
		break;
	case Attribute::Wind:
		power = *relational_param * 2 / 5 + 1;
		break;
	default:
		ErrorMessage("�����l�̐����ŕs���Ȓl���n����܂���");
		break;
	}

	if (power != 0) {
		*relational_param /= 2;
	}

	return AttributePower(_attribute, power);
}


