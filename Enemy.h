#pragma once
#include "Character.h"

/// <summary>
/// �G�N���X
/// </summary>
class Enemy : public Character {
public:
	Enemy(const std::string& _name);
	virtual ~Enemy() = default;
};

