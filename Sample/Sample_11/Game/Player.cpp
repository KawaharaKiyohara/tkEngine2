#include "stdafx.h"
#include "Player.h"

void Player::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool Player::Start()
{
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		50.0f,			//�����B
		m_position		//�����ʒu�B
	);
	
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animationClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animationClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animationClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	//���[�v�t���O��ݒ肷��B
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Thethief_H.cmo", m_animationClip, enAnimationClip_num);
	return true;
}

void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	m_moveSpeed += cameraForward * lStick_y * 200.0f;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * 200.0f;		//�E�����ւ̈ړ����x�����Z�B

	if (Pad(0).IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
	) {
		//�W�����v����B
		m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
		m_charaCon.Jump();		//�L�����N�^�[�R���g���[���[�ɃW�����v�������Ƃ�ʒm����B
	}
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
}
void Player::Update()
{
	//�ړ������B
	Move();
	
	//���[���h�s����X�V�B
	CQuaternion qBias;
	qBias.SetRotationDeg(CVector3::AxisX, 180.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(qBias);
}

