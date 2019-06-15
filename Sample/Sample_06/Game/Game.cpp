#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_spriteRender);
}
bool Game::Start()
{
	//�X�v���C�g���������B
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/mikyan.dds", 400, 300);

	return true;
}
void Game::Update()
{
	//��]
	CQuaternion qAdd;
	qAdd.SetRotationDeg(CVector3::AxisZ, 1.0f);
	m_rotation.Multiply(m_rotation, qAdd);
	//�ړ��B�X�e�B�b�N�̓��͂ňړ�������B
	m_position.x += Pad(0).GetLStickXF() * 10.0f;
	m_position.y += Pad(0).GetLStickYF() * 10.0f;
	m_position.z = 0.0f;	//2D��Ԃŕ`�悷��Ȃ�z��0�ł����B

	m_scale.x += Pad(0).GetRStickXF() * 0.1f;
	m_scale.y += Pad(0).GetRStickYF() * 0.1f;

	//���W�Ɖ�]��ݒ�B
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetRotation(m_rotation);
	m_spriteRender->SetScale(m_scale);
}

