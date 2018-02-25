/*!
 * @brief	�v���C���[�̃X�e�[�g�}�V�[���B
 */

#pragma once

#include "Player/FSM/PlayerState.h"
#include "Player/PlayerConst.h"

class CPlayerStateMachine : public IGameObject{
public:
	typedef std::function<void(CPlayerConst::EnState)> OnChangeState;
	CPlayerStateMachine(CPlayer* pl) :
		m_idleState(pl, this),
		m_runState(pl, this),
		m_walkState(pl, this),
		m_jumpState(pl, this)
	{
	}
	bool Start() override final;
	void Update() override final
	{
	}
	/*!
	* @brief	�X�e�[�g�̐؂�ւ��B
	*@param[in]	nextState	���̃X�e�[�g�B
	*/
	void ChangeState(CPlayerConst::EnState nextState);
	/*!
	 *@brief	�ړ��ł��邩����B
	 */
	bool IsMove() const
	{
		if (m_currentState == nullptr) {
			return false;
		}
		return m_currentState->IsMove();
	}
	/*!
	 *@brief	�d�͂̉e�����󂯂邩����B
	 */
	bool IsApplyGravity() const
	{
		if (m_currentState == nullptr) {
			return false;
		}
		return m_currentState->IsApplyGravity();
	}
	/*!
	 *@brief	���݂̏�Ԃ��擾�B
	 */
	CPlayerConst::EnState GetCurrentState() const
	{
		return m_state;
	}
	/*!
	 *@brief	�X�e�[�g�؂�ւ��̃��X�i�[��o�^�B
	 */
	void AddChangeStateListner(OnChangeState listner)
	{
		m_changeStateListener.push_back(listner);
	}
private:
	
	CPlayerConst::EnState m_state = CPlayerConst::enState_Invalid;
	IPlayerState* m_currentState = nullptr;
	CPlayerStateIdle m_idleState;
	CPlayerStateWalk m_walkState;
	CPlayerStateRun m_runState;
	CPlayerStateJump m_jumpState;
	
	std::vector<OnChangeState>	m_changeStateListener;	//!<�X�e�[�g�؂�ւ����X�i�[�B
};