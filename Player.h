#pragma once
#include "Character.h"



class Player : public Character {
public:
	Player();
	Player(const std::string& _name);
	virtual ~Player() = default;
};

