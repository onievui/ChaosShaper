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

	CharaParameter status = getStatus();

	std::cout << " 「 " << name << " 」" << "\n";
	std::cout << " Level    : " << status.level << "\n";
	std::cout << " HP       : " << status.hp << "/" << status.maxHp << "\n";
	std::cout << " Attack   : " << status.attack << "\n";
	std::cout << " Defence  : " << status.defence << "\n";
	std::cout << " Speed    : " << status.speed << "\n";
	std::cout << " Critical : " << status.critical << "\n";

	int exist_count = 0;

	std::cout << "  [Parts]" << "\n";
	for (const auto& part : getParts()) {
		std::cout << " " << part->getDetail() << "\n";
		++exist_count;
	}
	for (int i = exist_count; i < PARTS_MAX; ++i) {
		std::cout << " ---" << "\n";
	}
	exist_count = 0;

	std::cout << "  [Items]" << "\n";
	for (const auto& item : getItems()) {
		std::cout << " " << item->getDetail() << "\n";
	}
	for (int i = exist_count; i < ITEMS_MAX; ++i) {
		std::cout << " ---" << "\n";
	}
	std::cout << std::flush;
}


