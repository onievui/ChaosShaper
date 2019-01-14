#include "Player.h"
#include "Console.h"
#include <iostream>


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

/// <summary>
/// 情報の表示
/// </summary>
void Player::showInfo() {
	Console* console = Console::getIns();
	console->SetCursorPosition(0, 1);

	std::cout << " 「 " << name << " 」" << std::endl;
	std::cout << " Level    : " << parameter.level << std::endl;
	std::cout << " HP       : " << parameter.hp << "/" << parameter.maxHp << std::endl;
	std::cout << " Attack   : " << parameter.attack << std::endl;
	std::cout << " Defence  : " << parameter.defence << std::endl;
	std::cout << " Speed    : " << parameter.speed << std::endl;
	std::cout << " Critical : " << parameter.critical << std::endl;

	std::cout << "  [Parts]" << std::endl;
	for (const auto& part : getParts()) {
		std::cout << " " << part->getDetail() << std::endl;
	}

	std::cout << "  [Items]" << std::endl;
	for (const auto& item : getItems()) {
		std::cout << " " << item->getDetail() << std::endl;
	}

	for (int i = 0; i < 20; i++) {
		std::cout << "test" << i << std::endl;
	}

	std::cin.get();
}


