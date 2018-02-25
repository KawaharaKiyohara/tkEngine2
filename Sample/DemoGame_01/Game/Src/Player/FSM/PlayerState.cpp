/*!
 * @brief	�v���C���[�̃X�e�[�g
 */

#include "stdafx.h"
#include "Player/Player.h"
#include "Player/FSM/PlayerState.h"


namespace {
	const float WALK_THREDHOLD = 0.01f;							//!<������ԂɑJ�ڂ��鑬�x��臒l�B
	const float RUN_THREDHOLD = CPlayerConst::RUN_SPEED * 0.8f;	//!<�����ԂɑJ�ڂ��鑬�x��臒l�B
}
void CPlayerStateIdle::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD ;
	float moveSpeedScaler = moveSpeed.Length();
	if (Pad(0).IsPress(enButtonA)) {
		m_psm->ChangeState(CPlayerConst::enState_Jump);
	}else if (moveSpeedScaler > runThreadhold) {
		//�����ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Run);
	}
	else if (moveSpeedScaler > WALK_THREDHOLD) {
		//������ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Walk);
	}
}

void CPlayerStateWalk::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD;
	float moveSpeedScaler = moveSpeed.Length();
	
	if (Pad(0).IsPress(enButtonA)) {
		m_psm->ChangeState(CPlayerConst::enState_Jump);
	}else if (moveSpeedScaler > runThreadhold) {
		//�����ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Run);
	}
	else if (moveSpeedScaler < WALK_THREDHOLD) {
		//�ҋ@��ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Idle);
	}
}

void CPlayerStateRun::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD;
	float moveSpeedScaler = moveSpeed.Length();

	if (Pad(0).IsPress(enButtonA)) {
		m_psm->ChangeState(CPlayerConst::enState_Jump);
	}else if (moveSpeedScaler < runThreadhold) {
		//������ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Walk);
	}
	else if (moveSpeedScaler < WALK_THREDHOLD) {
		//�ҋ@��ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Idle);
	}
}
void CPlayerStateJump::Update()
{
	const CPlayerAnimator& animator = m_player->GetAnimator();
	CPlayerAnimator::EnAnimationClip clip = animator.GetCurrentAnimationClip();
	if ( clip != CPlayerAnimator::enAnimationClip_Jump
			&& clip != CPlayerAnimator::enAnimationClip_JumpEnd 
	) {
		//�W�����v�A�j���[�V�����ȊO���Đ�����Ă���B�B		
		CVector3 moveSpeed = m_player->GetMoveSpeed();
		float runThreadhold = RUN_THREDHOLD;
		float moveSpeedScaler = moveSpeed.Length();
		if (moveSpeedScaler > runThreadhold) {
			//�����ԂɑJ�ځB
			m_psm->ChangeState(CPlayerConst::enState_Run);
		}
		else if (moveSpeedScaler > WALK_THREDHOLD) {
			//������ԂɑJ�ځB
			m_psm->ChangeState(CPlayerConst::enState_Walk);
		}
		else {
			//�ҋ@��ԂɑJ�ځB
			m_psm->ChangeState(CPlayerConst::enState_Idle);
		}
	}
	else if (clip == CPlayerAnimator::enAnimationClip_JumpEnd) {
		if (m_waitTimer == 0) {
			//���n���[�V�������Đ����B
			CVector3 moveSpeed = m_player->GetMoveSpeed();
			float runThreadhold = RUN_THREDHOLD;
			float moveSpeedScaler = moveSpeed.Length();
			if (moveSpeedScaler > runThreadhold) {
				//�����ԂɑJ�ځB
				m_psm->ChangeState(CPlayerConst::enState_Run);
			}
			else if (moveSpeedScaler > WALK_THREDHOLD) {
				//������ԂɑJ�ځB
				m_psm->ChangeState(CPlayerConst::enState_Walk);
			}
			else if (animator.IsPlaying() == false) {
				//�ҋ@��ԂɑJ�ځB
				m_psm->ChangeState(CPlayerConst::enState_Idle);
			}
		}
		m_waitTimer = max(m_waitTimer--, 0);

	}
}

bool CPlayerStateJump::IsMove() const
{
	const CPlayerAnimator& animator = m_player->GetAnimator();
	if (animator.GetCurrentAnimationClip() == CPlayerAnimator::enAnimationClip_JumpEnd && m_waitTimer > 0) {
		return false;
	}
	return true;
}
/*!
*@brief	�d�͂̉e�����󂯂邩����B
*/
bool CPlayerStateJump::IsApplyGravity() const
{
	const CPlayerAnimator& animator = m_player->GetAnimator();
	if (animator.GetCurrentAnimationClip() == CPlayerAnimator::enAnimationClip_Jump
		&& animator.IsPlaying()
		) {
		//�W�����v���̃A�j���[�V�����Đ����͏d�͂̉e���͎󂯂Ȃ��B
		return false;
	}
	return true;
}