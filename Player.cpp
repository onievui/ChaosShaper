#include "Player.h"
#include "Console.h"
#include "ErrorMessage.h"
#include <iostream>


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() 
	: Character("unknown") {
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_name">���O</param>
Player::Player(const std::string& _name)
	: Character(_name) {
}

/// <summary>
/// ���̕\��
/// </summary>
void Player::showInfo() {
	Console* console = Console::getIns();
	console->setCursorPosition(0, 1);

	CharaParameter status = getStatus();
	
	std::cout << "  �u " << name << " �v" << "                         \n";
	std::cout << "  Level    : " << status.level << "                         \n";
	std::cout << "  HP       : " << status.hp << "/" << status.maxHp << "                         \n";
	std::cout << "  Attack   : " << status.attack << "                         \n";
	std::cout << "  Defence  : " << status.defence << "                         \n";
	std::cout << "  Speed    : " << status.speed << "                         \n";
	std::cout << "  Critical : " << status.critical << "                         \n";

	int exist_count = 0;

	std::cout << "   [Parts]" << "                         \n";
	for (const auto& part : getParts()) {
		std::cout << "  " << part->getDetail() << "                         \n";
		++exist_count;
	}
	for (int i = exist_count; i < PARTS_MAX; ++i) {
		std::cout << "  ---" << "                         \n";
	}
	exist_count = 0;

	std::cout << "   [Items]" << "                         \n";
	for (const auto& item : getItems()) {
		std::cout << "  " << item->getDetail() << "                         \n";
	}
	for (int i = exist_count; i < ITEMS_MAX; ++i) {
		std::cout << "  ---" << "                         \n";
	}
	std::cout << std::flush;
}

/// <summary>
/// HP�̍X�V
/// </summary>
void Player::updateHp() {
	Console* console = Console::getIns();
	console->setCursorPosition(0, 3);

	CharaParameter status = getStatus();

	std::cout << "  HP       : " << status.hp << "/" << status.maxHp << "                \n";
}

/// <summary>
/// ���ʂ���̂Ă�
/// </summary>
void Player::chooseDestroyPart() {
	Console* console = Console::getIns();
	constexpr KeyCode key_code_list[] = { KeyCode::KEY_UP,KeyCode::KEY_DOWN,KeyCode::KEY_ENTER };
	int current_index = 0;
	const int parts_num = parts.size();

	int cursor_pos = 9;
	console->setCursorPosition(0, cursor_pos);
	std::cout << "��" << std::endl;

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
			is_loop = false;
			break;
		default:
			ErrorMessage("�L�[���͂ŕs���Ȓl���n����܂���");
			break;
		}
		if (current_index == -1) {
			current_index = 0;
		}
		else if (current_index == parts_num) {
			--current_index;
		}

		//�J�[�\���\��
		console->setCursorPosition(0, cursor_pos);
		std::cout << "  " << std::endl;
		cursor_pos = 9 + current_index;
		console->setCursorPosition(0, cursor_pos);
		std::cout << "��" << std::endl;
	}

	removeEquipment(current_index);
	dropPart(current_index);
}

/// <summary>
/// �A�C�e������̂Ă�
/// </summary>
void Player::chooseDestroyItem() {
	Console* console = Console::getIns();
	constexpr KeyCode key_code_list[] = { KeyCode::KEY_UP,KeyCode::KEY_DOWN,KeyCode::KEY_ENTER };
	int current_index = 0;
	const int parts_num = parts.size();
	const int items_num = items.size();

	int cursor_pos = 10 + parts_num;
	console->setCursorPosition(0, cursor_pos);
	std::cout << "��" << std::endl;

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
			is_loop = false;
			break;
		default:
			ErrorMessage("�L�[���͂ŕs���Ȓl���n����܂���");
			break;
		}
		if (current_index == -1) {
			current_index = 0;
		}
		else if (current_index == items_num) {
			--current_index;
		}

		//�J�[�\���\��
		console->setCursorPosition(0, cursor_pos);
		std::cout << "  " << std::endl;
		cursor_pos = 8 + parts_num + current_index;
		console->setCursorPosition(0, cursor_pos);
		std::cout << "��" << std::endl;
	}

	removeEquipment(current_index);
	dropPart(current_index);
}

/// <summary>
/// ���R�ȑ����ύX
/// </summary>
void Player::editEquipment() {
	Console* console = Console::getIns();
	constexpr KeyCode key_code_list[] = { KeyCode::KEY_UP,KeyCode::KEY_DOWN,KeyCode::KEY_ENTER,(KeyCode)'z' };
	int current_type = 0;
	int current_index = 0;
	const int parts_num = parts.size();
	const int items_num = items.size();
	int cursor_pos = 9;
	if (parts_num == 0) {
		current_type = 1;
		cursor_pos = 10 + PARTS_MAX;
	}
	console->setCursorPosition(0, cursor_pos);
	std::cout << "��" << std::endl;

	bool is_loop = true;
	bool is_decide = false;
	while (is_loop) {
		int get_key = console->waitKeyWithKeyCode((int*)key_code_list, 4);
		//�J�[�\���ړ�
		switch ((KeyCode)get_key) {
		case KeyCode::KEY_UP:
			--current_index;
			break;
		case KeyCode::KEY_DOWN:
			++current_index;
			break;
		case KeyCode::KEY_ENTER:
			is_decide = true;
			break;
		case (KeyCode)'z':
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
				--current_index;
			}
		}

		//�����ύX����
		if (is_decide) {
			if (current_type == 0) {
				if (parts[current_index]->isEquipping()) {
					removeEquipment(current_index);
				}
			}
			else {
				Equipment* equip = dynamic_cast<Equipment*>(items[current_index].get());
				if (equip) {
					equipItem(items.begin() + current_index);
				}
			}
			showInfo();
			is_decide = false;
		}

		//�J�[�\���\��
		console->setCursorPosition(0, cursor_pos);
		std::cout << "  " << std::endl;
		if (current_type == 0) {
			cursor_pos = 9 + current_index;
		}
		else {
			if (current_index < (int)items.size()) {
				cursor_pos = 10 + PARTS_MAX + current_index;
			}
			else {
				if (current_index == 0) {
					current_type = 0;
				}
				else {
					--current_index;
				}
			}
		}
		console->setCursorPosition(0, cursor_pos);
		std::cout << "��" << std::endl;
	}
}

/// <summary>
/// ���x���A�b�v
/// </summary>
void Player::levelUp() {
	parameter.LevelUp();
}


