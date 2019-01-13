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
	void initialize() override;	//初期化
	void update() override;	    //更新
	void render() override;	    //描画
	void finalize() override;	//終了処理

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//シーン生成関数

private:
	void naming();
};