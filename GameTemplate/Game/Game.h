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
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 pos = CVector3::Zero;
	CCharacterController m_charaCon;
	CPhysicsGhostObject m_ghost;
};

