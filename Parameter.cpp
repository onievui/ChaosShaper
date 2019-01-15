#include "Parameter.h"
#include "Part.h"


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



AttackParameter::AttackParameter(const int _attack, const int _critical, const Part& _part)
	: attack(_attack)
	, attributePower(_part.getEquipment()->getAttributePower()) 
	, critical(_critical) {
	Equipment* equip = _part.getEquipment();
	int part_level = _part.getLevel();
	int equip_level = equip->getLevel();
	attack += ((part_level + 10) / 10) * (equip->getParameter().attack*(equip_level + 10) / 10);
	attributePower.power *= (equip_level + 10) / 10;
	critical += equip->getParameter().critical;
}
