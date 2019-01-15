#include "Enemy.h"
#include "Console.h"
#include <iostream>
#include <sstream>


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_name">名前</param>
Enemy::Enemy(const std::string& _name) 
	: Character(_name) {
}

/// <summary>
/// 情報の表示
/// </summary>
void Enemy::showInfo() {
	Console* console = Console::getIns();
	console->SetCursorPosition(0, 1);
	std::ostringstream sstream;
	CharaParameter status = getStatus();

	sstream << " 「 " << name << " 」";
	console->printRight(sstream, 1);
	sstream << status.level    << " :    Level";
	console->printRight(sstream, 1);
	sstream << status.hp       << "/" << status.maxHp << " :       HP";
	console->printRight(sstream, 1);
	sstream << status.attack   << " :   Attack";
	console->printRight(sstream, 1);
	sstream << status.defence  << " :  Defence";
	console->printRight(sstream, 1);
	sstream << status.speed    << " :    Speed";
	console->printRight(sstream, 1);
	sstream << status.critical << " : Critical";
	console->printRight(sstream, 1);


	console->printRight("[Parts]  ");
	for (const auto& part : getParts()) {
		console->printRight(part->getDetail(), 1);
	}
	
	console->printRight("[Items]  ");
	for (const auto& item : getItems()) {
		console->printRight(item->getDetail(), 1);
	}
	std::cout << std::flush;
}

/// <summary>
/// HPの更新
/// </summary>
void Enemy::updateHp() {
	Console* console = Console::getIns();
	console->SetCursorPosition(0, 3);
	std::ostringstream sstream;
	CharaParameter status = getStatus();

	sstream << "          " << status.hp << "/" << status.maxHp << " :       HP";
	console->printRight(sstream, 1);

	std::cout << std::flush;
}

