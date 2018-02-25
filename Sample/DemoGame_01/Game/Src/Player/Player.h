/*!
 * @brief	�v���C���[
 */

#pragma once

#include "Player/Animation/PlayerAnimator.h"
#include "Player/PlayerRenderer.h"
#include "Player/FSM/PlayerStateMachine.h"
#include "Player/PlayerMove.h"
#include "Player/PlayerTurn.h"

class CPlayer : public IGameObject {
public:
	/*!
	* @brief	�v���C���̃R���|�[�l���g�̃v���C�I���e�B�B
	*/
	enum EnPlayerComponentPrio {
		enPlayerComponentPrio_StateMachine,		//�X�e�[�g�}�V�[���B
		enPlayerComponentPrio_Move,				//�ړ������B
		enPlayerComponentPrio_Turn,				//���񏈗��B
		enPlayerComponentPrio_Animator,			//�A�j���[�^�B
		enPlayerComponentPrio_Renderer,			//�����_���[�B

	};
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CPlayer();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~CPlayer();
	/*!
	* @brief	�I���B
	*/
	void OnDestroy() override;
	/*!
	 * @brief	�X�^�[�g�B
	 */
	bool Start() override;
	/*!
	 * @brief	�X�V�B
	 */
	void Update() override;
	/*!
	 * @brief	�`��
	 *@param[in]	rc		�����_�����O�R���e�L�X�g�B
	 */
	void Render(CRenderContext& rc) override;
	/*!
	* @brief	���W���擾�B
	*/
	CVector3 GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	���W��ݒ�B
	*@param[in]	pos	���W�B
	*/
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/*!
	* @brief	��]�̎擾�B
	*/
	CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	/*!
	* @brief	��]�̐ݒ�B
	*/
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/*!
	* @brief	�v���C���[�����_���̎擾�B
	*/
	CPlayerRenderer& GetPlayerRenderer() 
	{
		return m_playerRenderer;
	}
	/*!
	 *@brief	�ړ��\������B
	 */
	bool IsPossibleMove() const
	{
		return m_playerStateMachine.IsMove();
	}
	/*!
	 *@brief	�ړ����x���擾�B
	 */
	CVector3 GetMoveSpeed() const
	{
		return m_playerMove.GetMoveSpeed();
	}
	/*!
	 *@brief	�v���C���[�̑O���������擾�B
	 */
	CVector3 GetForward() const
	{
		return m_forward;
	}
	/*!
	 *@brief	�v���C���[��XZ���ʂł̑O���������擾�B
	 */
	CVector3 GetForwardXZ() const
	{
		return m_forwardXZ;
	}
	/*!
	 *@brief	���݂̏�Ԃ��擾�B
	 */
	CPlayerConst::EnState GetCurrentState() const
	{
		return m_playerStateMachine.GetCurrentState();
	}
	
	/*!
	*@brief	�d�͂̉e�����󂯂邩����B
	*/
	bool IsApplyGravity() const
	{
		return m_playerStateMachine.IsApplyGravity();
	}
	/*!
	 *@brief	�A�j���[�^�[���擾�B
	 */
	const CPlayerAnimator& GetAnimator() const
	{
		return m_playerAnimator;
	}
	/*!
	 *@brief	�{�[���̖��O����{�[��ID�������B
	 */
	int FindBoneID(const wchar_t* boneName) const
	{
		return m_playerRenderer.GetSkinModelData().GetSkeleton().FindBoneID(boneName);
	}
	/*!
	*@brief	�{�[�����擾�B
	*/
	CBone* GetBone(int boneNo)
	{
		return m_playerRenderer.GetSkinModelData().GetSkeleton().GetBone(boneNo);
	}
	/*!
	*@brief	���x��������B
	*/
	void AddMoveSpeed(CVector3 speed)
	{
		m_playerMove.AddMoveSpeed(speed);
	}
	/*!
	*@brief	�X�e�[�g�؂�ւ��̃��X�i�[��o�^�B
	*/
	void AddChangeStateListner(CPlayerStateMachine::OnChangeState listner)
	{
		m_playerStateMachine.AddChangeStateListner(listner);
	}
	/*!
	 *@brief	�v���C���[���n�ʂɂ��邩����B
	 */
	bool IsOnGround() const
	{
		return m_playerMove.IsOnGround();
	}
	/*!
	 *@brief	�v���C���[�ɃW�����v���ł��邱�Ƃ�ʒm�B
	 */
	void Jump()
	{
		m_playerMove.Jump();
	}
private:
	CPlayerRenderer m_playerRenderer;				//�v���C�������_���B
	CPlayerAnimator m_playerAnimator;				//�A�j���[�^�B
	CPlayerMove	m_playerMove;						//�ړ������B
	CPlayerTurn m_playerTurn;						//���񏈗��B
	CPlayerStateMachine m_playerStateMachine;		//�X�e�[�g�}�V�[���B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CVector3 m_forward = CVector3::Front;			//�v���C���[�̑O�������B
	CVector3 m_forwardXZ = CVector3::Front;			//�v���C���[��XZ���ʂł̑O�������B
};
