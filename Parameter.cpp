#include "Parameter.h"


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

