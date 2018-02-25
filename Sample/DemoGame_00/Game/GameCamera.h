#pragma once

#include "Player.h"
#include "tkEngine/camera/tkSpringCamera.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void NotifyGameOver();
	void NotifyRestart();
	void NotifyGameClear();
private:
	Player* m_player;	//�v���C���[�B
	CSpringCamera m_springCamera;	//!<�o�l�J�����B
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
	bool m_isDebugCamera = false;
#endif
};

