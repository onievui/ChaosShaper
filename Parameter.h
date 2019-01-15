#pragma once
#include "Attribute.h"


class EquipParameter;

/// <summary>
/// �L�����N�^�[�p�����[�^�N���X
/// </summary>
class CharaParameter {
public:
	int level;
	int maxHp;
	int hp;
	int attack;
	int defence;
	int speed;
	int critical;

public:
	CharaParameter();
	CharaParameter(const int _lvl, const int _mhp, const int _atk, const int _def, const int _spd, const int _crt);

public:
	void addParameter(const EquipParameter& _equip_parameter);
};

/// <summary>
/// �����i�p�����[�^�N���X
/// </summary>
class EquipParameter {
public:
	int attack;
	int defence;
	int speed;
	int critical;

public:
	EquipParameter();
	EquipParameter(const int _atk, const int _def, const int _spd, const int _crt);
};


class Part;

/// <summary>
/// �U���p�����[�^�N���X
/// </summary>
class AttackParameter {
public:
	int attack;
	AttributePower attributePower;
	int critical;

public:
	AttackParameter(const int attack, const int _critical, const Part& _part);

};