#include "ResultScene.h"
#include "ShareDataManager.h"
#include "GameMain.h"
#include "Console.h"
#include "LogSystem.h"


/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
ResultScene::ResultScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene() {

}

/// <summary>
/// �V�[���̏�����
/// </summary>
void ResultScene::initialize() {
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void ResultScene::update() {
	ShareDataManager* share_data = ShareDataManager::getIns();
	Console* console = Console::getIns();

	int final_floor = share_data->getFloor();
	std::string player_name = share_data->getPlayerName();
	std::string enemy_name = share_data->getEnemyName();

	console->setCursorPosition(0, 18);
	std::stringstream text;
	text << "�u " << player_name << " �v�� " << final_floor << " �K�Łu" << enemy_name << "�v�ɓ|���ꂽ";
	console->printCenter(text.str());

	console->waitKey();
	console->clearScreen();
	LogSystem::getIns()->resetLog();
	implRequestScene->requestScene(SCENE_TITLE);
}


/// <summary>
/// �V�[���̕`��
/// </summary>
void ResultScene::render() {
	
}

/// <summary>
/// �V�[���̏I������
/// </summary>
void ResultScene::finalize() {
}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> ResultScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<ResultScene>(_impl));
}
