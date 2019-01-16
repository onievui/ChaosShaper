#include "Enemy.h"
#include "Console.h"
#include "ErrorMessage.h"
#include <iostream>
#include <sstream>


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_name">���O</param>
Enemy::Enemy(const std::string& _name) 
	: Character(_name) {
}

/// <summary>
/// ���̕\��
/// </summary>
void Enemy::showInfo() {
	Console* console = Console::getIns();
	console->setCursorPosition(0, 1);
	std::ostringstream sstream;
	CharaParameter status = getStatus();

	sstream << "                " << " �u " << name << " �v";
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
/// HP�̍X�V
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
/// ���肷��A�C�e���̑I��
/// </summary>
/// <param name="_choose_type">�I�������I�u�W�F�N�g�̎��</param>
/// <param name="_get_index">�I�������I�u�W�F�N�g�̃C���f�b�N�X</param>
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
	console->printRight("��");

	bool is_loop = true;
	while (is_loop) {
		int get_key = console->waitKeyWithKeyCode((int*)key_code_list, 3);
		//�J�[�\���ړ�
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
			ErrorMessage("�L�[���͂ŕs���Ȓl���n����܂���");
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
		//�J�[�\���\��
		console->setCursorPosition(0, cursor_pos);
		console->printRight("  ");
		if (current_type == 0) {
			cursor_pos = 9 + current_index;
		}
		else {
			cursor_pos = 10 + parts_num + current_index;
		}
		console->setCursorPosition(0, cursor_pos);
		console->printRight("��");

	}

}

