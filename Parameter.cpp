#include "Parameter.h"
#include "Part.h"
#include "Character.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
CharaParameter::CharaParameter()
	: CharaParameter(1,1,1,1,1,0) {
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_lvl">���x��</param>
/// <param name="_mhp">�ő�̗�</param>
/// <param name="_atk">�U����</param>
/// <param name="_def">�h���</param>
/// <param name="_spd">���x</param>
/// <param name="_crt">�N���e�B�J����</param>
CharaParameter::CharaParameter(const int _lvl, const int _mhp, const int _atk, const int _def, const int _spd, const int _crt)
	: level   (_lvl)
	, maxHp   (_mhp)
	, hp      (_mhp)
	, attack  (_atk)
	, defence (_def)
	, speed   (_spd)
	, critical(_crt) {
}

/// <summary>
/// �����p�����[�^�̒ǉ�
/// </summary>
/// <param name="_equip_parameter">�ǉ�����p�����[�^</param>
void CharaParameter::addParameter(const EquipParameter& _equip_parameter) {
	attack += _equip_parameter.attack;
	defence += _equip_parameter.defence;
	speed += _equip_parameter.speed;
	critical += _equip_parameter.critical;
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EquipParameter::EquipParameter() 
	: EquipParameter(0,0,0,0) {
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_atk">�U����</param>
/// <param name="_def">�h���</param>
/// <param name="_spd">���x</param>
/// <param name="_crt">�N���e�B�J����</param>
EquipParameter::EquipParameter(const int _atk, const int _def, const int _spd, const int _crt)
	: attack  (_atk)
	, defence (_def)
	, speed   (_spd)
	, critical(_crt) {
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_attack">�L�����̍U��</param>
/// <param name="_critical">�L�����̃N���e�B�J����</param>
AttackParameter::AttackParameter(const int _attack, const int _critical)
	: attack(_attack)
	, attributePower(AttributePower(Attribute::Normal, 0))
	, critical(_critical) {

}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_attack">�L�����̍U��</param>
/// <param name="_critical">�L�����̃N���e�B�J����</param>
/// <param name="_part">����</param>
AttackParameter::AttackParameter(const int _attack, const int _critical, const Part* _part)
	: attack(_attack*(_part->getLevel() + 10) / 10)
	, attributePower(_part->isEquipping() ? _part->getEquipment()->getAttributePower() : AttributePower(Attribute::Normal, 0))
	, critical(_critical) {
	//�����i������ꍇ
	if (_part->isEquipping()) {
		Equipment* equip = _part->getEquipment();
		attack += equip->getParameter().attack;
		critical += equip->getParameter().critical;
	}
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_chara">�L����</param>
DefenceParameter::DefenceParameter(Character* _chara) {
	defence.fill(0);
	int total_level = 0;
	for (const auto& part : _chara->getParts()) {
		//�U�����ʂ͔�΂�
		if (part->getPartType().equal(PartType::Arm)) {
			continue;
		}
		//�������Ă���ꍇ
		if (part->isEquipping()) {
			Equipment* equip = part->getEquipment();
			AttributePower attribute_power = equip->getAttributePower();
			defence[(int)Attribute::Normal] += equip->getParameter().defence;
			defence[(int)attribute_power.attribute] += attribute_power.power;
		}
		total_level += part->getLevel();
	}
	defence[(int)Attribute::Normal] += total_level;
}
