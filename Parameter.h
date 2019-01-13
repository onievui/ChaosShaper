#pragma once

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