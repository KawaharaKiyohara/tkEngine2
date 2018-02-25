/*!
 * @brief	�v���C���[�̃X�e�[�g�}�V�[���B
 */

#include "stdafx.h"
#include "Player/FSM/PlayerStateMachine.h"

void CPlayerStateMachine::ChangeState(CPlayerConst::EnState nextState)
{
	if (nextState == m_state) {
		//����X�e�[�g�ւ̑J�ځB
		return;
	}
	DeleteGO(m_currentState);
	m_state = nextState;
	switch (nextState) {
	case CPlayerConst::enState_Idle:
		m_currentState = &m_idleState;
		break;
	case CPlayerConst::enState_Run:
		m_currentState = &m_runState;
		break;
	case CPlayerConst::enState_Walk:
		m_currentState = &m_walkState;
		break;
	case CPlayerConst::enState_Jump:
		m_currentState = &m_jumpState;
		break;
	}
	//�X�e�[�g���؂�ւ�������Ƃ����X�i�[�ɒʒm�B
	for (auto func : m_changeStateListener) {
		func(nextState);
	}
	AddGO(GetPriority(), m_currentState, nullptr);
}
bool CPlayerStateMachine::Start()
{
	ChangeState(CPlayerConst::enState_Idle);
	return true;
}