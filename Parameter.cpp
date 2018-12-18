#include "Parameter.h"



CharaParameter::CharaParameter()
	: CharaParameter(1,1,1,1,1,0) {
}

CharaParameter::CharaParameter(const int _lvl, const int _mhp, const int _atk, const int _def, const int _spd, const int _crt)
	: level(_lvl)
	, maxHp(_mhp)
	, hp(_mhp)
	, attack(_atk)
	, defence(_def)
	, speed(_spd)
	, critical(_crt) {
}


EquipParameter::EquipParameter() 
	: EquipParameter(0,0,0,0) {
}

EquipParameter::EquipParameter(const int _atk, const int _def, const int _spd, const int _crt)
	: attack(_atk)
	, defence(_def)
	, speed(_spd)
	, critical(_crt) {
}
