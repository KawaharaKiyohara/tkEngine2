/*!
 * @brief	�v���C���[�̃A�j���[�^�[�B
 *@details
 * �v���C���[�̃A�j���[�V�����𐧌䂵�܂��B
 */

#pragma once

#include "Player/PlayerConst.h"

class CPlayer;
class CPlayerAnimator;

/*!
 *@brief	�W�����v�A�j���[�V��������B
 */
class CPlayerJumpAnimCtr : public IGameObject {
public:
	CPlayerJumpAnimCtr(CPlayer& pl, CPlayerAnimator& animator) :
		m_player(pl),
		m_animator(animator) {}
	bool Start() override final;
	void Update() override final;
	void OnDestroy() override final;
private:
	enum EnState {
		enState_PlayJump,
		enState_PlayJumpEnd,
	};
	EnState		m_state = enState_PlayJump;
	CPlayerAnimator& m_animator;	//!<�A�j���[�^�B
	CVector3 m_freezeBoneTranslation = CVector3::Zero;
	CPlayer& m_player;
	float m_timer = 0.0f;
};
/*!
 * @brief	�v���C���[�̃A�j���[�^�[�B
 */
class CPlayerAnimator : public IGameObject{
public:
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_JumpEnd,
		enANimationClip_Num,
	};
	CPlayerAnimator(CPlayer* player) :
		m_jumpAnimCtr(*player, *this)
	{
		m_player = player;
	}
	~CPlayerAnimator()
	{
	}
	bool Start() override;
	void Update() override;
	/*!
	 *@brief	�Đ����̃A�j���[�V�����N���b�v���擾�B
	 */
	EnAnimationClip GetCurrentAnimationClip() const
	{
		return m_currentAnimClip;
	}
	/*!
	 *@brief	�A�j���[�V�������Đ���������B
	 */
	bool IsPlaying() const
	{
		return m_skinModelRender->IsPlayingAnimation();
	}
	
	void PlayAnimation(EnAnimationClip animClip, float interpolateTime)
	{
		m_currentAnimClip = animClip;
		m_skinModelRender->PlayAnimation(animClip, interpolateTime);
	}
	/*!
	 *@brief	��Ԃ��ύX���ꂽ�Ƃ��̃R�[���o�b�N�֐��B
	 */
	void OnChangeState(CPlayerConst::EnState nextState);
	/*!
	*@brief	�t���[�Y�����Ă���{�[���̕��s�ړ��ʂ��擾�B
	*@details
	* �ŏI�|�[�Y�̃A�j���[�V���������B
	*/
	CVector3 GetFreezeBoneTranslate() const
	{
		return m_skinModelRender->GetFreezeBoneTranslate();
	}
	/*!
	*@brief	�A�j���[�V�����C�x���g���N�������ɌĂ΂�鏈���B
	*/
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);
private:
	EnAnimationClip m_currentAnimClip = enAnimationClip_Idle;		//!<���ݍĐ����̃A�j���[�V�����N���b�v�B
	CAnimationClip m_animClips[enANimationClip_Num];	//!<�A�j���[�V�����N���b�v�G�B
	CPlayer* m_player = nullptr;						//!<�v���C���[�����_���[�B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPlayerJumpAnimCtr m_jumpAnimCtr;
};