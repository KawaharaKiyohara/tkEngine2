#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	void InitCamera();
	void InitSkinModelRender();
	void InitGhostObject();
private:
	prefab::CSkinModelRender* m_backGroundRender = nullptr;	//�w�i�̕`�揈���B
	prefab::CSkinModelRender* m_playerRender = nullptr;		//�v���C���[�̕`�揈���B
	CCharacterController m_charaCon;
	CPhysicsGhostObject m_ghostObject;						//�S�[�X�g�I�u�W�F�N�g�Ƃ��S�B

	prefab::CPointLight* m_pointLig = nullptr;				//�|�C���g���C�g�B
	prefab::CSoundSource* m_explosionSoundSource = nullptr;
};

