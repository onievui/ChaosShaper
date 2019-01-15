#pragma once
#include "Character.h"


/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public Character {
public:
	Player();
	Player(const std::string& _name);
	virtual ~Player() = default;

public:
	void showInfo();
	virtual void updateHp() override;
};

