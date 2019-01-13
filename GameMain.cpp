#include "GameMain.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "ShareDataManager.h"
#include "ErrorMessage.h"


Game::Game() {

}

Game::~Game() {

}



void Game::initialize(void) {
	addScene(SCENE_TITLE, TitleScene::create);
	addScene(SCENE_PLAY, PlayScene::create);
	addScene(SCENE_RESULT, ResultScene::create);
	nowScene = sceneFactoryMethods[SCENE_TITLE](this);
	nextScene = SCENE_NONE;
	ShareDataManager::getIns()->initialize();
}


void Game::update(void) {
	if (nextScene != SCENE_NONE) {
		changeScene();
	}
	nowScene->update();
}


void Game::render(void) {
	nowScene->render();
}


void Game::finalize(void) {

}

void Game::requestScene(const SceneID _id) {
	if (_id <= SCENE_NONE || _id >= SCENE_NUM) {
		ErrorMessage("シーンの切り替え要求で不正な値が渡されました");
		return;
	}
	nextScene = _id;
}

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

//----------------------------------------------------------------------
//! @brief シーンの切り替え処理
//!
//! @param[in] _id 次のシーンID
//!
//! @return なし
//----------------------------------------------------------------------
void Game::changeScene(void) {
	nowScene->finalize();
	if (nextScene <= SCENE_NONE || nextScene >= SCENE_NUM) {
		ErrorMessage("シーンの追切り替え処理で不正なシーンIDが渡されました");
		return;
	}
	nowScene = sceneFactoryMethods[nextScene](this);
	nextScene = SCENE_NONE;
}
