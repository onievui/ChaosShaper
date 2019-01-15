#include "PlayScene.h"
#include "ShareDataManager.h"
#include "Portion.h"
#include "Console.h"
#include "BattleSystem.h"
#include "LogSystem.h"
#include <iostream>
#include <conio.h>
#include <sstream>



/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl)
	, playState(PlayState::Naming)
	, nowFloor()
	, player()
	, enemy() {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene() {

}

/// <summary>
/// �V�[���̏�����
/// </summary>
void PlayScene::initialize() {
	nowFloor = 1;
	player = std::make_unique<Player>();
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void PlayScene::update() {

	switch (playState) {
	case PlayScene::PlayState::Naming:
		naming();
		break;
	case PlayScene::PlayState::Battle:
		battle();
		break;
	default:
		break;
	}

	

}

/// <summary>
/// �V�[���̕`��
/// </summary>
void PlayScene::render() {

}

/// <summary>
/// �V�[���̏I������
/// </summary>
void PlayScene::finalize() {

}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> PlayScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<PlayScene>(_impl));
}

/// <summary>
/// ���O�̐ݒ�
/// </summary>
void PlayScene::naming() {
	Console* console = Console::getIns();
	char in_name[256];
	while (true) {
		console->ClearScreen();
		console->SetCursorPosition(0, 18);
		console->printCenter("���Ȃ��̖��O�������Ă�������");
		console->printCenter("-> ", false);
		std::cin.getline(in_name, 256);

		console->ClearScreen();
		console->SetCursorPosition(0, 18);
		std::stringstream text;
		text << "�u " << in_name << " �v�ł����H";
		console->printCenter(text.str());
		console->printCenter("�͂��i1�j �������i2�j ", false);
		char in;
		while (true) {
			in = (char)_getch();
			if (in == '1' || in == '2') {
				break;
			}
		}
		std::cout << std::endl;
		if (in == '1') {
			break;
		}
	}
	console->ClearScreen();
	console->SetCursorPosition(0, 18);
	std::string tmp_name = in_name;
	player->setName(tmp_name);
	player->setStatus(CharaParameter(1, 50, 3, 3, 3, 0));
	std::stringstream text;
	text << "�u " << tmp_name << " �v�̖`�������n�܂�c";
	console->printCenter(text.str());
	console->SetCursorVisibility(CursorVisibility::CURSOR_INVISIBLE);
	Sleep(3000);
	playState = PlayState::Battle;
}

void PlayScene::battle() {
	Console* console = Console::getIns();
	std::stringstream text;

	console->ClearScreen();
	text << nowFloor << "�K";
	console->printCenter(text.str());
	Sleep(1000);

	player->showInfo();
	enemy = std::make_unique<Enemy>("�X���C��");
	enemy->setStatus(CharaParameter(1, 10, 2, 2, 2, 0));
	enemy->showInfo();

	LogSystem::getIns()->drawFlame();
	LogSystem::getIns()->addLog(enemy->getName() + std::string("�����ꂽ�I"));
	std::cin.get();

	auto battleSystem = std::make_unique<BattleSystem>(player.get(), enemy.get());
	battleSystem->battle();

	std::cin.get();
}
