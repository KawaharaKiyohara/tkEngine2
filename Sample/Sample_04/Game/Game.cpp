#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�f�B���N�V�������C�g(���z���݂����Ȃ���)���V�[���ɒǉ��B
	m_lightDir.Set(0.707f, -0.707f, 0.0f);
	m_lig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	m_lig->SetDirection(m_lightDir);
	//���C�g�̐F��ݒ�B
	m_lig->SetColor({ 300.5f, 300.5f, 300.5f, 1.0f });


	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 15.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 15.0f, 30.0f });
	MainCamera().Update();

	//���f���f�[�^�����[�h�B
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);

	return true;
}
void Game::Update()
{
	//���C�g���񂷁B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f);
	qRot.Multiply(m_lightDir);
	m_lig->SetDirection(m_lightDir);
	//���[���h�s����X�V�B
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Game::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}