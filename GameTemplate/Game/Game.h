#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	CVector3 pos = CVector3::Zero;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_bgSkinModelRender = nullptr;	//�w�i�̃X�L�����f�������_���[�B
	std::vector<prefab::CDirectionLight*> m_directionLight;		//�f�B���N�V�������C�g�B
	CShaderResourceView m_spec;
};

