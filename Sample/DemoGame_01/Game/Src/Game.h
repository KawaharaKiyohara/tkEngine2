#pragma once

#include "Camera/GameCamera.h"
#include "Player/Player.h"
#include "BackGround/BackGround.h"
#include "tkEngine/light/tkPointLight.h"

class Enemy;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void OnDestroy() override;
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
private:
	CPlayer m_player;			//!<�v���C���[
	CBackGround m_bg;			//!<�w�i�B
	CGameCamera m_gameCamera;	//!<�Q�[���J�����B
	std::vector<Enemy*> m_enemyList;	//!<�G�̃��X�g�B
	std::vector<prefab::CPointLight*>	m_pointLightList;	//!<�|�C���g���C�g�̃��X�g�B
	prefab::CDirectionLight* m_directionLig = nullptr;	//!<�f�B���N�V�������C�g�B
};

