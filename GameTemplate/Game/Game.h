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
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_bgSkinModelRender = nullptr;
	CShaderResourceView m_spec;
};

