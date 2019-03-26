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
	MainCamera().SetFar(10000.0f);
	MainCamera().Update();

	//�X�L�����f�������_���[���쐬�B
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	return true;
}

void Game::Update()
{
	return;
	if (m_rotateMode == 0) {
		//������]���[�h�B
		//�܂��AY�������1�x��]����N�H�[�^�j�I�����v�Z����B
		CQuaternion qAddRot;
		qAddRot.SetRotationDeg(CVector3::AxisY, 1.0f);
		//m_rotation��qAddRot����Z���đ��
		//�N�H�[�^�j�I���͏�Z����Ɖ�]�����������B
		m_rotation *= qAddRot;
		//���������N�H�[�^�j�I�����X�L�����f�������_���[�ɓ`����B
		m_skinModelRender->SetRotation(m_rotation);
	}
	else if (m_rotateMode == 1) {
		//�X�e�B�b�N�ŉ�]�����郂�[�h�B
		CQuaternion qAddRotY, qAddRotX;
		qAddRotY.SetRotationDeg( CVector3::AxisY, Pad(0).GetLStickXF() );
		qAddRotX.SetRotationDeg( CVector3::AxisX, Pad(0).GetLStickYF() );
		//��]�����Z����B
		m_rotation *= qAddRotY;
		m_rotation *= qAddRotX;
		//���������N�H�[�^�j�I�����X�L�����f�������_���[�ɓ`����B
		m_skinModelRender->SetRotation(m_rotation);
	}
	if (Pad(0).IsTrigger(enButtonA) == true) {
		//A�{�^������������A��]���[�h��ύX����B
		if (m_rotateMode == 0) {
			m_rotateMode = 1;
		}else if (m_rotateMode == 1) {
			m_rotateMode = 0;
		}
	}
}
