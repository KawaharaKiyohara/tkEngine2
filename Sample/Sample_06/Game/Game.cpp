#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�e�N�X�`�������[�h�B
	m_texture.CreateFromDDSTextureFromFile(L"sprite/mikyan.dds");
	m_sprite.Init(m_texture, 400, 300);
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

	//���[���h�s��̍X�V�B
	m_sprite.Update(m_position, m_rotation, CVector3::One);
}

void Game::PostRender(CRenderContext& rc)
{
	//�X�v���C�g��`��B
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
