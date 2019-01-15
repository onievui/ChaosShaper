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
	text << "「 " << tmp_name << " 」の冒険が今始まる…";
	console->printCenter(text.str());
	console->SetCursorVisibility(CursorVisibility::CURSOR_INVISIBLE);
	Sleep(3000);
	playState = PlayState::Battle;
}

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
	enemy->showInfo();

	LogSystem::getIns()->drawFlame();
	LogSystem::getIns()->addLog(enemy->getName() + std::string("が現れた！"));
	std::cin.get();

	auto battleSystem = std::make_unique<BattleSystem>(player.get(), enemy.get());
	battleSystem->battle();

	std::cin.get();
}
