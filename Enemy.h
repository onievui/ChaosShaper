#pragma once
#include "Character.h"

/// <summary>
/// “GƒNƒ‰ƒX
/// </summary>
class Enemy : public Character {
public:
	Enemy(const std::string& _name);
	virtual ~Enemy() = default;

public:
	void showInfo();
	virtual void updateHp() override;
	void chooseGetObject(int* _choose_type, int* _get_index);
};

