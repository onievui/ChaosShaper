#pragma once

#include "SceneID.h"


/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X
/// </summary>
class RequestSceneListener {
public:
	RequestSceneListener() = default;
	virtual ~RequestSceneListener() = default;

public:
	//�V�[���̐؂�ւ��v��
	virtual void requestScene(const SceneID _id) = 0;
};