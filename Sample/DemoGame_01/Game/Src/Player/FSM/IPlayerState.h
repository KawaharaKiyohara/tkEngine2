/*!
 * @brief	�v���C���[�̃X�e�[�g�̃C���^�[�t�F�[�X
 */

#pragma once

class CPlayerStateMachine;
class CPlayer;
class IPlayerState : public IGameObject {
public:
	IPlayerState(CPlayer* pl, CPlayerStateMachine* psm) :
		m_player(pl),
		m_psm(psm)
	{
	}
	/*!
	 * @brief	�ړ��ł��邩����
	 */
	virtual bool IsMove() const
	{
		return true;
	}
	/*!
	 *@brief	�d�͂̉e�����󂯂邩����B
	 */
	virtual bool IsApplyGravity() const
	{
		return true;
	}
protected:
	CPlayer* m_player = nullptr;
	CPlayerStateMachine* m_psm = nullptr;
};