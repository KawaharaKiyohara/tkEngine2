#pragma once

#include "GameActor.h"
//�΂˃J�������g�p�������ꍇ��tkSpringCamera.h���C���N���[�h����K�v������B
#include "tkEngine/camera/tkSpringCamera.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	GameActor* m_actor;	//�v���C���[�B
	CVector3 m_toCameraPos;	//
	CSpringCamera m_springCamera; //�΂˃J�����B
};

