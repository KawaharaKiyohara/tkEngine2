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
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	//�X�L�����f�������_���[���쐬�B
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	return true;
}

void Game::Update()
{
	//�܂��AY�������1�x��]����N�H�[�^�j�I�����v�Z����B
	CQuaternion qAddRot;
	qAddRot.SetRotationDeg(CVector3::AxisY, 1.0f);
	//m_rotation��qAddRot����Z���đ��
	//�N�H�[�^�j�I���͏�Z����Ɖ�]�����������B
	m_rotation *= qAddRot;
	//���������N�H�[�^�j�I�����X�L�����f�������_���[�ɓ`����B
	m_skinModelRender->SetRotation(m_rotation);
}
