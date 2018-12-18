#pragma once



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
	CharaParameter()
		: level(1)
		, maxHp(1)
		, hp(1)
		, attack(1)
		, defence(1)
		, speed(1)
		, critical(0) {
	}
};