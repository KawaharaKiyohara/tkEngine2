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
	//�A�N�^�[�������B
	m_gameActor = FindGO<GameActor>("�ÎE��");
	return true;
}
void Player::Update()
{
	if (m_gameActor->IsPlayRecord()) {
		//�L�^���Đ����Ȃ烊�^�[���B
		return;
	}
	//���K�P�@�L�[�{�[�h��A�������ꂽ�獶�ɐ���A
	//�@�@�@�@�L�[�{�[�h��D�������ꂽ��E�ɐ���o����悤�ɂ��Ȃ����B
	if (GetAsyncKeyState('W')) {
		//�O�ɐi�ށB
		m_gameActor->AddCommand(&m_commandWalk);
	}
	else {
		//����������Ă��Ȃ��̂őҋ@�B
		m_gameActor->AddCommand(&m_commandIdle);
	}
}