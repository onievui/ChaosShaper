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
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl)
	, playState(PlayState::Naming)
	, nowFloor()
	, player()
	, enemy() {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene() {

}

/// <summary>
/// シーンの初期化
/// </summary>
void PlayScene::initialize() {
	nowFloor = 1;
	player = std::make_unique<Player>();
}

/// <summary>
/// シーンの更新
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
/// シーンの描画
/// </summary>
void PlayScene::render() {

}

/// <summary>
/// シーンの終了処理
/// </summary>
void PlayScene::finalize() {

}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> PlayScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<PlayScene>(_impl));
}

/// <summary>
/// 名前の設定
/// </summary>
void PlayScene::naming() {
	Console* console = Console::getIns();
	char in_name[256];
	while (true) {
		console->ClearScreen();
		console->SetCursorPosition(0, 18);
		console->printCenter("あなたの名前を教えてください");
		console->printCenter("-> ", false);
		std::cin.getline(in_name, 256);

		console->ClearScreen();
		console->SetCursorPosition(0, 18);
		std::stringstream text;
		text << "「 " << in_name << " 」ですか？";
		console->printCenter(text.str());
		console->printCenter("はい（1） いいえ（2） ", false);
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
	text << "「 " << tmp_name << " 」の冒険が今始まる…";
	console->printCenter(text.str());
	console->SetCursorVisibility(CursorVisibility::CURSOR_INVISIBLE);
	Sleep(3000);
	playState = PlayState::Battle;
}

/// <summary>
/// 戦闘処理
/// </summary>
void PlayScene::battle() {
	Console* console = Console::getIns();
	std::stringstream text;

	console->ClearScreen();
	text << nowFloor << "階";
	console->printCenter(text.str());
	Sleep(1000);

	player->showInfo();
	enemy = std::make_unique<Enemy>("スライム");
	enemy->setStatus(CharaParameter(1, 10, 2, 2, 2, 0));
	enemy->addPart(std::make_unique<Part>(PartType::Arm, 1));
	enemy->addItem(std::make_unique<Equipment>("ひのきの棒", 1, PartType::Arm, EquipParameter(1, 0, 0, 1), AttributePower(Attribute::Normal, 0)));
	enemy->showInfo();

	LogSystem::getIns()->drawFlame();
	LogSystem::getIns()->addLog(enemy->getName() + std::string("が現れた！"));
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
/// 勝利処理
/// </summary>
void PlayScene::win() {
	LogSystem::getIns()->resetLog();
	getFase();
	equipFase();
}

/// <summary>
/// 部位・アイテムの獲得
/// </summary>
void PlayScene::getFase() {
	LogSystem* log_system = LogSystem::getIns();

	enemy->autoRemoveEquipment();
	enemy->showInfo();

	log_system->addLog("相手の部位かアイテムを一つ入手できます");
	int get_type, get_index;
	enemy->chooseGetObject(&get_type, &get_index);

	//部位を選んだ場合
	if (get_type == 0) {
		std::unique_ptr<Part> part = enemy->dropPart(get_index);
		if (player->isPartsFull()) {
			player->chooseDestroyPart();
		}
		player->addPart(std::move(part));
	}
	//アイテムを選んだ場合
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
/// 装備品の設定
/// </summary>
void PlayScene::equipFase() {

}

/// <summary>
/// 敗北処理
/// </summary>
void PlayScene::lose() {
	Console::getIns()->ClearScreen();
	implRequestScene->requestScene(SceneID::SCENE_RESULT);
}
