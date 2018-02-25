/*!
 * @brief	�v���C���[�̈ړ������B
 */

#pragma once

#include "tkEngine/character/tkCharacterController.h"

class CPlayer;
class CGameCamera;

class CPlayerMove : public IGameObject{
public:
	CPlayerMove( CPlayer* pl );
	~CPlayerMove();
	bool Start() override final;
	void Update() override final;
	/*!
	 *@brief	�ړ����x�̎擾�B
	 */
	CVector3 GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/*!
	 *@brief	���x��������B
	 */
	void AddMoveSpeed(CVector3 speed)
	{
		m_addMoveSpeed += speed;
	}
	/*!
	 *@brief	�W�����v���ł��邱�Ƃ�ʒm
	 */
	void Jump()
	{
		m_charaCon.Jump();
	}
	/*!
	 *@brief	�v���C���[���n�ʂɂ��邩�ǂ�������B
	 */
	bool IsOnGround() const
	{
		return m_charaCon.IsOnGround();
	}
	/*!
	 *@brief	�v���C���[�̏�Ԃ��؂�ւ�����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	 */
	void OnChangeState(CPlayerConst::EnState nextState);
private:
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���B
	CPlayer* m_player = nullptr;
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	CVector3 m_addMoveSpeed = CVector3::Zero;	//���Z�����ړ����x�B
	CGameCamera* m_gameCamera = nullptr;
	float m_accelTime = 0.0f;
};