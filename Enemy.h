#pragma once
#include "Character.h"

/// <summary>
/// “GƒNƒ‰ƒX
/// </summary>
class Enemy : public Character {
public:
	Enemy(const std::string& _name);
	virtual ~Enemy() = default;
};

