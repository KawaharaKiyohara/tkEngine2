/*!
 * @brief	�v���C���[�̃X�e�[�g�B
 */

#pragma once

#include "Player/FSM/IPlayerState.h"

/*!
 * @brief	�ҋ@�X�e�[�g�B
 */
class CPlayerStateIdle : public IPlayerState{
public:
	CPlayerStateIdle(CPlayer* pl, CPlayerStateMachine* psm) :
		IPlayerState(pl, psm)
	{
	}
	virtual ~CPlayerStateIdle()
	{
	}
	void Update() override final;
private:
	
};

/*!
 *@brief	�����X�e�[�g�B
 */
class CPlayerStateWalk : public IPlayerState {
public:
	CPlayerStateWalk(CPlayer* pl, CPlayerStateMachine* psm) :
		IPlayerState(pl, psm) {}
	void Update() override final;
};
/*!
 *@brief	����X�e�[�g�B
 */
class CPlayerStateRun : public IPlayerState {
public:
	CPlayerStateRun(CPlayer* pl, CPlayerStateMachine* psm) :
		IPlayerState(pl, psm) {}
	void Update() override final;
};
/*!
*@brief	�W�����v�X�e�[�g�B
*/
class CPlayerStateJump : public IPlayerState {
public:
	CPlayerStateJump(CPlayer* pl, CPlayerStateMachine* psm) :
		IPlayerState(pl, psm) {}
	bool Start() override final
	{
		m_waitTimer = 2;
		
		return true;
	}
	void Update() override final;
	/*!
	* @brief	�ړ��ł��邩����
	*/
	bool IsMove() const override;
	/*!
	 *@brief	�d�͂̉e�����󂯂邩����B
	 */
	bool IsApplyGravity() const override;
private:
	int m_waitTimer = 1;
};