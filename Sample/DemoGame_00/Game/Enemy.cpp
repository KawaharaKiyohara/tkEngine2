#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
Enemy::Enemy() :
	m_pathMoveLoop(this, m_movePath)
{
}


Enemy::~Enemy()
{
	DeleteGO(m_modelRender);
}
bool Enemy::Start()
{
	

	m_animClip[enAnimationClip_idle].Load(L"animData/enemy/idle.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].Load(L"animData/enemy/run.tka");
	m_animClip[enAnimationClip_run].SetLoopFlag(true);

	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/enemy.cmo", m_animClip, enAnimationClip_num);

	m_modelRender->SetShadowCasterFlag(true);
	m_modelRender->SetShadowReceiverFlag(true);
	m_modelRender->PlayAnimation(enAnimationClip_idle);

	m_charaCon.Init(20.0f, 00.0f, m_position);
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	return true;
}

void Enemy::NotifyRestart()
{
	m_isFindPlayer = false;
}
void Enemy::SearchPlayer()
{
	//�G����v���C���[�Ɍ������x�N�g�����v�Z�B
	CVector3 toPlayer = m_player->GetPosition() - m_position;
	//�����āAtoPlayer���������Ă݂�B
	/*dbg::DrawVector(
		toPlayer,
		m_position);*/
	if (toPlayer.Length() < 400.0f) {
		//����p�𔻒�B
		toPlayer.Normalize();

		float angle = acosf(toPlayer.Dot(m_forward));
		if (fabsf(angle) < CMath::PI * 0.25f) {
			//����p45�x�ȓ��B
			//�Q�[���ɃQ�[���I�[�o�[��ʒm�B
			Game* game = FindGO<Game>("Game");
			game->NotifyGameOver();
			m_isFindPlayer = true;
		}
	}
}
void Enemy::Update()
{
	if (!m_game->IsGameOver() && !m_game->IsGameClear()) {
		SearchPlayer();
		m_pathMoveLoop.Update();
	}
	const auto scale = CVector3( 3.0f, 3.0f, 3.0f );
	m_modelRender->SetPRS(m_position, m_rotation, scale);

	auto mRot = CMatrix::Identity;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
}
