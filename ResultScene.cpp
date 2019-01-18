#include "ResultScene.h"
#include "ShareDataManager.h"
#include "GameMain.h"
#include "Console.h"
#include "LogSystem.h"


/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
ResultScene::ResultScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene() {

}

/// <summary>
/// シーンの初期化
/// </summary>
void ResultScene::initialize() {
}

/// <summary>
/// シーンの更新
/// </summary>
void ResultScene::update() {
	ShareDataManager* share_data = ShareDataManager::getIns();
	Console* console = Console::getIns();

	int final_floor = share_data->getFloor();
	std::string player_name = share_data->getPlayerName();
	std::string enemy_name = share_data->getEnemyName();

	console->setCursorPosition(0, 18);
	std::stringstream text;
	text << "「 " << player_name << " 」は " << final_floor << " 階で「" << enemy_name << "」に倒された";
	console->printCenter(text.str());

	console->waitKey();
	console->clearScreen();
	LogSystem::getIns()->resetLog();
	implRequestScene->requestScene(SCENE_TITLE);
}


/// <summary>
/// シーンの描画
/// </summary>
void ResultScene::render() {
	
}

/// <summary>
/// シーンの終了処理
/// </summary>
void ResultScene::finalize() {
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> ResultScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<ResultScene>(_impl));
}
