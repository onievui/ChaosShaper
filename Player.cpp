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
	console->SetCursorPosition(0, 1);

	CharaParameter status = getStatus();

	std::cout << "  �u " << name << " �v" << "                \n";
	std::cout << "  Level    : " << status.level << "                \n";
	std::cout << "  HP       : " << status.hp << "/" << status.maxHp << "                \n";
	std::cout << "  Attack   : " << status.attack << "                \n";
	std::cout << "  Defence  : " << status.defence << "                \n";
	std::cout << "  Speed    : " << status.speed << "                \n";
	std::cout << "  Critical : " << status.critical << "                \n";

	int exist_count = 0;

	std::cout << "   [Parts]" << "                \n";
	for (const auto& part : getParts()) {
		std::cout << "  " << part->getDetail() << "                \n";
		++exist_count;
	}
	for (int i = exist_count; i < PARTS_MAX; ++i) {
		std::cout << "  ---" << "                \n";
	}
	exist_count = 0;

	std::cout << "   [Items]" << "                \n";
	for (const auto& item : getItems()) {
		std::cout << "  " << item->getDetail() << "                \n";
	}
	for (int i = exist_count; i < ITEMS_MAX; ++i) {
		std::cout << "  ---" << "                \n";
	}
	std::cout << std::flush;
}

/// <summary>
/// HP�̍X�V
/// </summary>
void Player::updateHp() {
	Console* console = Console::getIns();
	console->SetCursorPosition(0, 3);

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
	console->SetCursorPosition(0, cursor_pos);
	std::cout << "��" << std::endl;

	bool is_loop = true;
	while (is_loop) {
		int get_key = console->WaitKeyWithKeyCode((int*)key_code_list, 3);
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
		console->SetCursorPosition(0, cursor_pos);
		std::cout << "  " << std::endl;
		cursor_pos = 9 + current_index;
		console->SetCursorPosition(0, cursor_pos);
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
	console->SetCursorPosition(0, cursor_pos);
	std::cout << "��" << std::endl;

	bool is_loop = true;
	while (is_loop) {
		int get_key = console->WaitKeyWithKeyCode((int*)key_code_list, 3);
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
		console->SetCursorPosition(0, cursor_pos);
		std::cout << "  " << std::endl;
		cursor_pos = 8 + parts_num + current_index;
		console->SetCursorPosition(0, cursor_pos);
		std::cout << "��" << std::endl;
	}

	removeEquipment(current_index);
	dropPart(current_index);
}


