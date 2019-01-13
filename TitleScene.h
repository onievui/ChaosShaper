#pragma once

#include "AbstractScene.h"



/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public AbstractScene {
private:

public:
	TitleScene(RequestSceneListener* _impl);
	~TitleScene();

public:
	void initialize() override;	//初期化
	void update() override;	    //更新
	void render() override;	    //描画
	void finalize() override;	//終了処理

	static std::unique_ptr<AbstractScene> create(RequestSceneListener* _impl);	//シーン生成関数
};