#include "GameMain.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "ShareDataManager.h"
#include "ErrorMessage.h"


/// <summary>
/// コンストラクタ
/// </summary>
Game::Game() {

}

/// <summary>
/// デストラクタ
/// </summary>
Game::~Game() {

}

/// <summary>
/// 初期化処理
/// </summary>
void Game::initialize(void) {
	addScene(SCENE_TITLE, TitleScene::create);
	addScene(SCENE_PLAY, PlayScene::create);
	addScene(SCENE_RESULT, ResultScene::create);
	nowScene = sceneFactoryMethods[SCENE_TITLE](this);
	nextScene = SCENE_NONE;
	ShareDataManager::getIns()->initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void Game::update(void) {
	if (nextScene != SCENE_NONE) {
		changeScene();
	}
	nowScene->update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::render(void) {
	nowScene->render();
}

/// <summary>
/// 終了処理
/// </summary>
void Game::finalize(void) {

}

/// <summary>
/// シーン切り替え要求
/// </summary>
/// <param name="_id">シーンID</param>
void Game::requestScene(const SceneID _id) {
	if (_id <= SCENE_NONE || _id >= SCENE_NUM) {
		ErrorMessage("シーンの切り替え要求で不正な値が渡されました");
		return;
	}
	nextScene = _id;
}

/// <summary>
/// シーンの追加
/// </summary>
/// <param name="_id">シーンID</param>
/// <param name="_scene_factory_method">シーン生成処理</param>
void Game::addScene(const SceneID _id, SceneFactoryMethod _scene_factory_method) {
	if (_id <= SCENE_NONE || _id >= SCENE_NUM) {
		ErrorMessage("シーンの追加で不正なシーンIDが渡されました");
		return;
	}
	if (_scene_factory_method == nullptr) {
		ErrorMessage("シーンの追加で不正な生成関数が渡されました");
		return;
	}

	sceneFactoryMethods[_id] = _scene_factory_method;
}

/// <summary>
/// シーン切り替え
/// </summary>
void Game::changeScene(void) {
	nowScene->finalize();
	if (nextScene <= SCENE_NONE || nextScene >= SCENE_NUM) {
		ErrorMessage("シーンの追切り替え処理で不正なシーンIDが渡されました");
		return;
	}
	nowScene = sceneFactoryMethods[nextScene](this);
	nextScene = SCENE_NONE;
}
