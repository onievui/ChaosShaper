#include "Parameter.h"
#include "Part.h"
#include "Character.h"


/// <summary>
/// コンストラクタ
/// </summary>
CharaParameter::CharaParameter()
	: CharaParameter(1,1,1,1,1,0) {
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_lvl">レベル</param>
/// <param name="_mhp">最大体力</param>
/// <param name="_atk">攻撃力</param>
/// <param name="_def">防御力</param>
/// <param name="_spd">速度</param>
/// <param name="_crt">クリティカル率</param>
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
/// 装備パラメータの追加
/// </summary>
/// <param name="_equip_parameter">追加するパラメータ</param>
void CharaParameter::addParameter(const EquipParameter& _equip_parameter) {
	attack += _equip_parameter.attack;
	defence += _equip_parameter.defence;
	speed += _equip_parameter.speed;
	critical += _equip_parameter.critical;
}


/// <summary>
/// コンストラクタ
/// </summary>
EquipParameter::EquipParameter() 
	: EquipParameter(0,0,0,0) {
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_atk">攻撃力</param>
/// <param name="_def">防御力</param>
/// <param name="_spd">速度</param>
/// <param name="_crt">クリティカル率</param>
EquipParameter::EquipParameter(const int _atk, const int _def, const int _spd, const int _crt)
	: attack  (_atk)
	, defence (_def)
	, speed   (_spd)
	, critical(_crt) {
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_attack">キャラの攻撃</param>
/// <param name="_critical">キャラのクリティカル率</param>
AttackParameter::AttackParameter(const int _attack, const int _critical)
	: attack(_attack)
	, attributePower(AttributePower(Attribute::Normal, 0))
	, critical(_critical) {

}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_attack">キャラの攻撃</param>
/// <param name="_critical">キャラのクリティカル率</param>
/// <param name="_part">部位</param>
AttackParameter::AttackParameter(const int _attack, const int _critical, const Part* _part)
	: attack(_attack*(_part->getLevel() + 10) / 10)
	, attributePower(_part->isEquipping() ? _part->getEquipment()->getAttributePower() : AttributePower(Attribute::Normal, 0))
	, critical(_critical) {
	//装備品がある場合
	if (_part->isEquipping()) {
		Equipment* equip = _part->getEquipment();
		attack += equip->getParameter().attack;
		critical += equip->getParameter().critical;
	}
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_chara">キャラ</param>
DefenceParameter::DefenceParameter(Character* _chara) {
	defence.fill(0);
	int total_level = 0;
	for (const auto& part : _chara->getParts()) {
		//攻撃部位は飛ばす
		if (part->getPartType().equal(PartType::Arm)) {
			continue;
		}
		//装備している場合
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
