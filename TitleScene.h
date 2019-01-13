#pragma once

#include "AbstractScene.h"



/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public AbstractScene {
private:

public:
	TitleScene(RequestSceneListener* _impl);
	~TitleScene();

public:
	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�
};