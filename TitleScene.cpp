#include "TitleScene.h"
#include "GameMain.h"
#include "Console.h"
#include <iostream>



/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
TitleScene::TitleScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene() {

}

/// <summary>
/// シーンの初期化
/// </summary>
void TitleScene::initialize() {

}

/// <summary>
/// シーンの更新
/// </summary>
void TitleScene::update() {
	Console* console = Console::getIns();

	console->setCursorPosition(0, 3);

	std::cout << "　　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << "\n";
	std::cout << "　　■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << "\n";
	std::cout << "　　■　■■■■　■　　■　■■■■　■■■■　■■■■　　　■■■■　■　　■　■■■■　■■■■　■■■■　■■■■　■" << "\n";
	std::cout << "　　■　■　　　　■　　■　■　　■　■　　■　■　　　　　　■　　　　■　　■　■　　■　■　　■　■　　　　■　　■　■" << "\n";
	std::cout << "　　■　■　　　　■■■■　■■■■　■　　■　■■■■　　　■■■■　■■■■　■■■■　■■■■　■■■■　■■■■　■" << "\n";
	std::cout << "　　■　■　　　　■　　■　■　　■　■　　■　　　　■　　　　　　■　■　　■　■　　■　■　　　　■　　　　■　■　　■" << "\n";
	std::cout << "　　■　■■■■　■　　■　■　　■　■■■■　■■■■　　　■■■■　■　　■　■　　■　■　　　　■■■■　■　　■　■" << "\n";
	std::cout << "　　■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■" << "\n";
	std::cout << "　　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << "\n";


	std::cout << "\n\n\n\n";
	console->printCenter("press any key");
	console->setCursorVisibility(CursorVisibility::CURSOR_INVISIBLE);
	console->waitKey();
	console->setCursorVisibility(CursorVisibility::CURSOR_VISIBLE);
	implRequestScene->requestScene(SCENE_PLAY);
}


/// <summary>
/// シーンの描画
/// </summary>
void TitleScene::render() {
	
}

/// <summary>
/// シーンの終了処理
/// </summary>
void TitleScene::finalize() {

}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> TitleScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<TitleScene>(_impl));
}
