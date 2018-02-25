#include "stdafx.h"
#include "Game.h"


void Game::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool Game::Start()
{
	
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 35.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 35.0f, 80.0f });
	MainCamera().Update();
	

	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"animData/run.tka");
	m_animClips[enAnimationClip_walk].Load(L"animData/walk.tka");
	//���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	//�����V���b�g�Đ��Œ�~����B
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//�X�L�����f�������_���[���쐬�B
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Thethief_H.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->PlayAnimation(enAnimationClip_run);
	
	return true;
}
void Game::Update()
{
	//3dsMax���90�x�񂳂�Ă���̂ŁA�������ŉ񂷁B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 180.0f);
	//A�{�^���������ꂽ��ҋ@���[�V�������Đ�����B
	if (Pad(0).IsTrigger(enButtonA)) {
		//Play�֐��̑������͕⊮���ԁB
		//�ҋ@���[�V�����̐؂�ւ��͕⊮���Ԃ�ݒ肵�Ă��Ȃ��̂ŁA�A�j���[�V�������p�L���ƕς��B
		m_skinModelRender->PlayAnimation(enAnimationClip_idle);
	}
	//B�{�^���������ꂽ�瑖��A�j���[�V�������Đ�����B
	else if (Pad(0).IsTrigger(enButtonB)) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2f);
	}
	//Y�{�^���������ꂽ������A�j���[�V�������Đ�����B
	else if (Pad(0).IsTrigger(enButtonY)) {
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2f);
	}
	
	//��]��ݒ�B
	m_skinModelRender->SetRotation(qRot);
}
