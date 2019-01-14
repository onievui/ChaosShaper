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
	std::stringstream sstream;

	sstream << " 「 " << name << " 」";
	console->printRight(sstream, 1);
	sstream << parameter.level    << " :    Level";
	console->printRight(sstream, 1);
	sstream << parameter.hp       << "/" << parameter.maxHp << " :       HP";
	console->printRight(sstream, 1);
	sstream << parameter.attack   << " :   Attack";
	console->printRight(sstream, 1);
	sstream << parameter.defence  << " :  Defence";
	console->printRight(sstream, 1);
	sstream << parameter.speed    << " :    Speed";
	console->printRight(sstream, 1);
	sstream << parameter.critical << " : Critical";
	console->printRight(sstream, 1);

	int exist_count = 0;

	console->printRight("[Parts]  ");
	for (const auto& part : getParts()) {
		console->printRight(part->getDetail(), 1);
		++exist_count;
	}
	for (int i = exist_count; i < PARTS_MAX; ++i) {
		console->printRight("--- ");
	}
	exist_count = 0;

	console->printRight("[Items]  ");
	for (const auto& item : getItems()) {
		console->printRight(item->getDetail(), 1);
		++exist_count;
	}
	for (int i = exist_count; i < ITEMS_MAX; ++i) {
		console->printRight("--- ");
	}
}

