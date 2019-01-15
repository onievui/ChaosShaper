#pragma once
#include "Attribute.h"
#include <array>


class EquipParameter;

/// <summary>
/// キャラクターパラメータクラス
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
/// 装備品パラメータクラス
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
/// 攻撃パラメータクラス
/// </summary>
class AttackParameter {
public:
	int attack;
	AttributePower attributePower;
	int critical;

public:
	AttackParameter(const int _attack, const int _critical);
	AttackParameter(const int _attack, const int _critical, const Part* _part);

};


class Character;

/// <summary>
/// 防御パラメータクラス
/// </summary>
class DefenceParameter {
public:
	std::array<int, (int)Attribute::Num> defence;

public:
	DefenceParameter(Character* _chara);

};