#pragma once

#include "Player.h"

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
	Player* m_player;	//�v���C���[�B
	CVector3 m_toCameraPos;	//
};

