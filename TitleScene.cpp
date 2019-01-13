#include "TitleScene.h"
#include "GameMain.h"

/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
TitleScene::TitleScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene() {

}

/// <summary>
/// �V�[���̏�����
/// </summary>
void TitleScene::initialize() {

}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void TitleScene::update() {
	implRequestScene->requestScene(SCENE_PLAY);
}


/// <summary>
/// �V�[���̕`��
/// </summary>
void TitleScene::render() {
	
}

/// <summary>
/// �V�[���̏I������
/// </summary>
void TitleScene::finalize() {

}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> TitleScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<TitleScene>(_impl));
}
