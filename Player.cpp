#include "Player.h"


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() 
	: Character("unknown") {
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_name">名前</param>
Player::Player(const std::string& _name)
	: Character(_name) {
}


