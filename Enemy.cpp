#include "Enemy.h"
#include "Console.h"
#include "ErrorMessage.h"
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
	console->setCursorPosition(0, 1);
	std::ostringstream sstream;
	CharaParameter status = getStatus();

	sstream << "                " << " 「 " << name << " 」";
	console->printRight(sstream, 2);
	sstream << "                " << status.level    << " :    Level";
	console->printRight(sstream, 2);
	sstream << "                " << status.hp       << "/" << status.maxHp << " :       HP";
	console->printRight(sstream, 2);
	sstream << "                " << status.attack   << " :   Attack";
	console->printRight(sstream, 2);
	sstream << "                " << status.defence  << " :  Defence";
	console->printRight(sstream, 2);
	sstream << "                " << status.speed    << " :    Speed";
	console->printRight(sstream, 2);
	sstream << "                " << status.critical << " : Critical";
	console->printRight(sstream, 2);

	int exist_count = 0;

	console->printRight("                [Parts]   ");
	for (const auto& part : getParts()) {
		console->printRight("                " + part->getDetail(), 2);
		++exist_count;
	}
	
	console->printRight("                [Items]   ");
	for (const auto& item : getItems()) {
		console->printRight("                " + item->getDetail(), 2);
		++exist_count;
	}
	
	for (int i = exist_count; i < PARTS_MAX + ITEMS_MAX; ++i) {
		console->printRight("                              ", 2);
	}

	std::cout << std::flush;
}

/// <summary>
/// HPの更新
/// </summary>
void Enemy::updateHp() {
	Console* console = Console::getIns();
	console->setCursorPosition(0, 3);
	std::ostringstream sstream;
	CharaParameter status = getStatus();

	sstream << "                " << status.hp << "/" << status.maxHp << " :       HP";
	console->printRight(sstream, 2);

	std::cout << std::flush;
}

/// <summary>
/// 入手するアイテムの選択
/// </summary>
/// <param name="_choose_type">選択したオブジェクトの種類</param>
/// <param name="_get_index">選択したオブジェクトのインデックス</param>
void Enemy::chooseGetObject(int* _choose_type, int* _get_index) {
	Console* console = Console::getIns();
	constexpr KeyCode key_code_list[] = { KeyCode::KEY_UP,KeyCode::KEY_DOWN,KeyCode::KEY_ENTER };
	int current_type = 0;
	int current_index = 0;
	const int parts_num = parts.size();
	const int items_num = items.size();
	int cursor_pos = 9;
	if (parts_num == 0) {
		current_type = 1;
		cursor_pos = 10;
	}
	console->setCursorPosition(0, cursor_pos);
	console->printRight("←");

	bool is_loop = true;
	while (is_loop) {
		int get_key = console->waitKeyWithKeyCode((int*)key_code_list, 3);
		//カーソル移動
		switch ((KeyCode)get_key) {
		case KeyCode::KEY_UP:
			--current_index;
			break;
		case KeyCode::KEY_DOWN:
			++current_index;
			break;
		case KeyCode::KEY_ENTER:
			*_choose_type = current_type;
			*_get_index = current_index;
			is_loop = false;
			break;
		default:
			ErrorMessage("キー入力で不正な値が渡されました");
			break;
		}
		if (current_type == 0) {
			if (current_index == -1) {
				current_index = 0;
			}
			else if (current_index == parts_num) {
				if (items_num > 0) {
					current_type = 1;
					current_index = 0;
				}
				else {
					--current_index;
				}
			}
		}
		else {
			if (current_index == -1) {
				if (parts_num > 0) {
					current_type = 0;
					current_index = parts_num - 1;
				}
				else {
					++current_index;
				}
			}
			else if (current_index == items_num) {
				current_index = items_num - 1;
			}
		}
		//カーソル表示
		console->setCursorPosition(0, cursor_pos);
		console->printRight("  ");
		if (current_type == 0) {
			cursor_pos = 9 + current_index;
		}
		else {
			cursor_pos = 10 + parts_num + current_index;
		}
		console->setCursorPosition(0, cursor_pos);
		console->printRight("←");

	}

}

