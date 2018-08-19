#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_charaCon.Init(30, 100, m_position);
}
Player::~Player()
{
	DeleteGO(m_skinModelRender);
}
void Player::Move()
{

}
void Player::Update()
{
	//�v���C���[�̈ړ������B
	Move();
	m_moveSpeed.x = Pad(0).GetLStickXF() * 200.0f;
	m_moveSpeed.y -= 20.0f;
	m_moveSpeed.z = Pad(0).GetLStickYF() * 200.0f;
	if (Pad(0).IsTrigger(enButtonA)) {
		m_moveSpeed.y = 400.0f;
	}
	m_position = m_charaCon.Execute(m_moveSpeed);
	m_skinModelRender->SetPosition(m_position);

	//�X�^�[�Ƃ����蔻����s���B
	//�܂��AGame�N���X�̃C���X�^���X�ɃA�N�Z�X����B
	Game* game = FindGO<Game>("Game");
	for (int i = 0; i < 5; i++) {
		Star* star = game->m_star[i];
		if (star != nullptr) {
			//�����̔���B
			CVector3 diff = star->m_position - m_position;
			if (diff.Length() < 50.0f) {
				//������20�ȉ��ɂȂ�����A�����폜�B
				game->m_star[i] = nullptr;
				//���̎擾�����J�E���g�A�b�v�B
				game->m_numGetStarCount++;
				DeleteGO(star);
			}
		}
	}
}
