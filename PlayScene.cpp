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
	case PlayState::Naming:
		naming();
		break;
	case PlayState::Battle:
		battle();
		break;
	case PlayState::Win:
		win();
		break;
	case PlayState::Lose:
		lose();
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
			std::cout << in << std::endl;
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
	player->setStatus(CharaParameter(1, 30, 3, 3, 3, 0));
	std::stringstream text;
	text << "�u " << tmp_name << " �v�̖`�������n�܂�c";
	console->printCenter(text.str());
	console->SetCursorVisibility(CursorVisibility::CURSOR_INVISIBLE);
	Sleep(3000);
	playState = PlayState::Battle;
}

/// <summary>
/// �퓬����
/// </summary>
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
	enemy->addPart(std::make_unique<Part>(PartType::Arm, 1));
	enemy->addItem(std::make_unique<Equipment>("�Ђ̂��̖_", 1, PartType::Arm, EquipParameter(1, 0, 0, 1), AttributePower(Attribute::Normal, 0)));
	enemy->showInfo();

	LogSystem::getIns()->drawFlame();
	LogSystem::getIns()->addLog(enemy->getName() + std::string("�����ꂽ�I"));
	console->WaitKey();

	auto battleSystem = std::make_unique<BattleSystem>(player.get(), enemy.get());
	if (battleSystem->battle()) {
		playState = PlayState::Win;
	}
	else {
		playState = PlayState::Lose;
	}
}

/// <summary>
/// ��������
/// </summary>
void PlayScene::win() {
	LogSystem::getIns()->resetLog();
	getFase();
	equipFase();
}

/// <summary>
/// ���ʁE�A�C�e���̊l��
/// </summary>
void PlayScene::getFase() {
	LogSystem* log_system = LogSystem::getIns();

	enemy->autoRemoveEquipment();
	enemy->showInfo();

	log_system->addLog("����̕��ʂ��A�C�e���������ł��܂�");
	int get_type, get_index;
	enemy->chooseGetObject(&get_type, &get_index);

	//���ʂ�I�񂾏ꍇ
	if (get_type == 0) {
		std::unique_ptr<Part> part = enemy->dropPart(get_index);
		if (player->isPartsFull()) {
			player->chooseDestroyPart();
		}
		player->addPart(std::move(part));
	}
	//�A�C�e����I�񂾏ꍇ
	else {
		std::unique_ptr<Item> item = enemy->dropItem(get_index);
		if (player->isItemsFull()) {
			player->chooseDestroyItem();
		}
		player->addItem(std::move(item));
	}
	player->showInfo();
	enemy->showInfo();

	Console::getIns()->WaitKey();
}

/// <summary>
/// �����i�̐ݒ�
/// </summary>
void PlayScene::equipFase() {

}

/// <summary>
/// �s�k����
/// </summary>
void PlayScene::lose() {
	Console::getIns()->ClearScreen();
	implRequestScene->requestScene(SceneID::SCENE_RESULT);
}
