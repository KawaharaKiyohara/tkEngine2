#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}
bool Player::Start()
{
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		50.0f,			//�����B
		m_position		//�����ʒu�B
	);
	//�A�j���[�V�������������B
	InitAnimation();
	return true;
}
void Player::InitAnimation()
{
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animationClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animationClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animationClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	//���[�v�t���O��ݒ肷��B
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	//�A�j���[�V�������������B
	m_animation.Init(m_skinModel, m_animationClip, enAnimationClip_num);
	//�ҋ@�A�j���[�V�����𗬂��B
	m_animation.Play(enAnimationClip_idle);
}
void Player::AnimationControl()
{
	//�A�j���[�V������i�߂�B
	m_animation.Update(GameTime().GetFrameDeltaTime());
}
void Player::Update()
{
	//���̃t���[���̈ړ��ʂ����߂�B
	m_moveSpeed.x = Pad(0).GetLStickXF() * -150.0f;
	m_moveSpeed.z = Pad(0).GetLStickYF() * -150.0f;
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	if (Pad(0).IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
	) {
		//�W�����v����B
		m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
		m_charaCon.Jump();		//�L�����N�^�[�R���g���[���[�ɃW�����v�������Ƃ�ʒm����B
	}
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);

	//�A�j���[�V�����R���g���[���B
	AnimationControl();
	//���[���h�s����X�V�B
	CQuaternion qBias;
	qBias.SetRotationDeg(CVector3::AxisX, 180.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
	m_skinModel.Update(m_position, qBias, CVector3::One);
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
