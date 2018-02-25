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
	MainCamera().SetTarget({ 0.0f, 35.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 35.0f, 80.0f });
	MainCamera().Update();

	//���f���f�[�^�����[�h�B
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);

	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"animData/run.tka");
	m_animClips[enAnimationClip_walk].Load(L"animData/walk.tka");
	//���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	//�����V���b�g�Đ��Œ�~����B
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//���[�h�����A�j���[�V�����N���b�v���g���ăA�j���[�V����������������B
	m_animation.Init(m_skinModel, m_animClips, enAnimationClip_Num);

	m_animation.Play(enAnimationClip_run);
	return true;
}
void Game::Update()
{
	//3dsMax���90�x�񂳂�Ă���̂ŁA�������ŉ񂷁B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	//A�{�^���������ꂽ��ҋ@���[�V�������Đ�����B
	if (Pad(0).IsTrigger(enButtonA)) {
		//Play�֐��̑������͕⊮���ԁB
		//�ҋ@���[�V�����̐؂�ւ��͕⊮���Ԃ�ݒ肵�Ă��Ȃ��̂ŁA�A�j���[�V�������p�L���ƕς��B
		m_animation.Play(enAnimationClip_idle);	
	}
	//B�{�^���������ꂽ�瑖��A�j���[�V�������Đ�����B
	else if (Pad(0).IsTrigger(enButtonB)) {
		m_animation.Play(enAnimationClip_run, 0.2f);
	}
	//Y�{�^���������ꂽ������A�j���[�V�������Đ�����B
	else if (Pad(0).IsTrigger(enButtonY)) {
		m_animation.Play(enAnimationClip_walk, 0.2f);
	}
	
	//���[���h�s����X�V�B
	m_skinModel.Update(CVector3::Zero, qRot, CVector3::One, CSkinModel::enFbxUpAxisY);
}
void Game::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}