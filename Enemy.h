#pragma once
#include "Character.h"


class Enemy : public Character {
public:
	Enemy(const std::string& _name);
	virtual ~Enemy() = default;
};

