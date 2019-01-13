#include "PlayScene.h"
#include "ShareDataManager.h"
#include "Portion.h"
#include <iostream>
#include <conio.h>

/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl)
	, playState(PlayState::Naming)
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
		std::cin.get();
		break;
	default:
		break;
	}

	//auto equip = std::make_unique<Equipment>("sword", 10, PartType::Arm, EquipParameter(), AttributePower(Attribute::Fire, 200));
	//auto pot = std::make_unique<Portion>("pot", 10, 100);
	//auto part = std::make_unique<Part>(PartType::Arm);
	//player->addPart(std::move(part));
	//player->addItem(std::move(equip));
	//player->addItem(std::move(pot));

	//std::cout << "name : " + player->getName() << std::endl;
	//std::cout << std::endl;

	//CharaParameter param = player->getStatus();
	//std::cout << "level   : " << param.level << std::endl;
	//std::cout << "hp      : " << param.hp << std::endl;
	//std::cout << "attack  : " << param.attack << std::endl;
	//std::cout << "defence : " << param.defence << std::endl;
	//std::cout << std::endl;


	//for (const auto& item : player->getItems()) {
	//	std::cout << item->getDetail() << std::endl;
	//}
	//std::cout << std::endl;

	//for (const auto& part : player->getParts()) {
	//	std::cout << part->getDetail() << std::endl;
	//}
	//std::cout << std::endl;

	//player->autoEquipping();

	//for (const auto& part : player->getParts()) {
	//	std::cout << part->getDetail() << std::endl;
	//}
	//std::cout << std::endl;

	//for (const auto& item : player->getItems()) {
	//	std::cout << item->getDetail() << std::endl;
	//}
	//std::cout << std::endl;

	//player->removeEquipment(0);

	//for (const auto& part : player->getParts()) {
	//	std::cout << part->getDetail() << std::endl;
	//}
	//std::cout << std::endl;

	//for (const auto& item : player->getItems()) {
	//	std::cout << item->getDetail() << std::endl;
	//}
	//std::cout << std::endl;


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
	std::string tmp_name;
	while (true) {
		std::cout << "あなたの名前を教えてください -> ";
		std::cin >> tmp_name;

		std::cout << "「 " << tmp_name << " 」さんですか？\n"
			      << "はい（1） いいえ（2）";
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
	player->setName(tmp_name);
	playState = PlayState::Battle;
	std::cout << "ようこそ「 " << tmp_name << " 」さん\n" << std::endl;
}
