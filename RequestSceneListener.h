#pragma once

#include "SceneID.h"


/// <summary>
/// シーン切り替えインタフェース
/// </summary>
class RequestSceneListener {
public:
	RequestSceneListener() = default;
	virtual ~RequestSceneListener() = default;

public:
	//シーンの切り替え要求
	virtual void requestScene(const SceneID _id) = 0;
};