#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include <memory>



class PlayScene : public AbstractScene {
private:
	enum class PlayState {
		Naming,
		Battle,
	};

private:
	PlayState playState;
	std::unique_ptr<Player> player;
	std::unique_ptr<Enemy> enemy;


public:
	PlayScene(RequestSceneListener* _impl);
	~PlayScene();

public:
	void initialize() override;	//������
	void update() override;	    //�X�V
	void render() override;	    //�`��
	void finalize() override;	//�I������

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//�V�[�������֐�

private:
	void naming();
};