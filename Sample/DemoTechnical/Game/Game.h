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
	std::vector< prefab::CDirectionLight*> m_dirLights;			//���s�����̃��X�g
	prefab::CSkinModelRender* m_charaModelRender = nullptr;		//�L�����N�^�[�̃��f�������_���[�B
	prefab::CSkinModelRender* m_groundModelRender = nullptr;	//�n�ʂ̃��f�������_���[�B
	prefab::CSky* m_sky = nullptr;								//��B
	CShaderResourceView m_charaNormalMap;						//�L�����̖@���}�b�v�B
	CShaderResourceView m_charaSpecMap;							//�L�����̃X�y�L�����}�b�v�B
	CQuaternion m_charaRot = CQuaternion::Identity;
};

