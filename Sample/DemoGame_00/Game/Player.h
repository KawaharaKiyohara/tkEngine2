/*!
 * @brief	�v���C���[
 */

#pragma once

#include "tkEngine/character/tkCharacterController.h"
class Game;
class Player : public IGameObject {
public:

	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
	 *@brief	�Q�[���I�[�o�[��ʌ��B
	 */
	void NotifyGameOver();
	/*!
	 *@brief	���X�^�[�g��ʒm�B
	 */
	void NotifyRestart();
	/*!
	 *@brief	�Q�[���N���A�[�B
	 */
	void NotifyGameClear();
	/*!
	 *@brief	�N���A�ł���H
	 */
	bool IsPossibleClear() const
	{
		if (m_state != enState_Jump
			&& m_state != enState_GameOver
			&& m_state != enState_WaitStartGameClear
			&& m_state != enState_GameClear)
		{
			return true;
		}
		return false;
	}
	/*!
	*@brief	�X�L�����f���̎擾�B
	*/
	CSkinModel& GetModel()
	{
		return m_modelRender->GetSkinModel();
	}
private:
	void UpdateFSM();
	void Move();
	void Turn();
	void AnimationController();
	
private:
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_Clear,
		enAnimationClip_num,
	};
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Jump,
		enState_GameOver,
		enState_WaitStartGameClear,
		enState_GameClear,
	};
	prefab::CSkinModelRender* m_modelRender = nullptr;	//!<���f�������_���B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CAnimationClip m_animClip[enAnimationClip_num];
	
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<�L�����N�^�p�̃��C�g�B
	CCharacterController m_charaCon;		//�L�����N�^�R���g���[���B
	CVector3 m_moveSpeed = CVector3::Zero;
	CShaderResourceView m_normalMap;		//�@���}�b�v�B
	CShaderResourceView m_specMap;			//�X�y�L�����}�b�v�B
	CVector3 m_forward;						//�v���C���[�̑O���B
	EnState m_state = enState_Idle;
	Game* m_game = nullptr;
	float m_moveSpeedWhenStartJump;			//�W�����v���J�n�����Ƃ��̈ړ����x�B
	float m_timer = 0.0f;
};