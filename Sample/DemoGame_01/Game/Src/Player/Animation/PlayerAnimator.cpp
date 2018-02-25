/*!
 * @brief	�v���C���[�̃A�j���[�^�B
 */

#include "stdafx.h"
#include "Player/Player.h"
#include "Player/PlayerRenderer.h"
#include "Player/Animation/PlayerAnimator.h"
#include "tkEngine/graphics/effect/tkEffect.h"

bool CPlayerJumpAnimCtr::Start()
{
	m_animator.PlayAnimation(CPlayerAnimator::enAnimationClip_Jump, 0.2f);
	//@todo FootIK�p�̃p�����[�^��ݒ肷��B
	//�v���C���[�ɃW�����v���ł��邱�Ƃ�ʒm����B
	m_player.Jump();
	m_state = enState_PlayJump;
	m_freezeBoneTranslation = CVector3::Zero;
	m_timer = 0.0f;

	return true;
}
void CPlayerJumpAnimCtr::Update()
{
	switch (m_state) {
	case enState_PlayJump: {
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer < 0.2f) {
			//�W�����v���[�V�������J�n����āA2�b�Ԃ��炢�͂����ƃW�����v�ʒm�����Ă����B
			m_player.Jump();
		}
		
		if (m_player.IsOnGround()) {
			//�n�ʂɍ~�藧�����B
			m_animator.PlayAnimation(CPlayerAnimator::enAnimationClip_JumpEnd, 0.1f);
			m_state = enState_PlayJumpEnd;
		}else {
			//�W�����v���[�V��������footstep��Z�����̈ړ��ʂ�Y�����̈ړ����x�ɂ���B
			CVector3 freezeBoneTranslate = m_animator.GetFreezeBoneTranslate();
			//�O�̃t���[���Ƃ̍������v�Z����B
			CVector3 moveSpeed = freezeBoneTranslate - m_freezeBoneTranslation;
			moveSpeed *= (1.0f / GameTime().GetFrameDeltaTime());	//���x��cm/�b�ɕϊ�����B
			moveSpeed.x = 0.0f;
			moveSpeed.y = -moveSpeed.z;
			moveSpeed.z = 0.0f;
			m_player.AddMoveSpeed(moveSpeed);
			m_freezeBoneTranslation = freezeBoneTranslate;
		}
	}break;
	case enState_PlayJumpEnd:
		if (m_animator.IsPlaying() == false) {
			//�I���B
		}
		break;
	}
}


void CPlayerJumpAnimCtr::OnDestroy()
{
}


void CPlayerAnimator::OnInvokeAnimationEvent(
	const wchar_t* animClipName, 
	const wchar_t* eventName
)
{
	if (wcscmp(eventName, L"FootStepSE") == 0) {
		auto soundSource = NewGO<prefab::CSoundSource>(0);
		soundSource->Init("sound/Footstep_00.wav");
		soundSource->Play(false);
	}
}a
bool CPlayerAnimator::Start()
{
	//�X�e�[�g�؂芷���̃��X�i�[��o�^����B
	m_player->AddChangeStateListner([&](auto nextState) {
		OnChangeState(nextState);
	});
	int boneNo = m_player->FindBoneID(L"thief_Bip01_Footsteps");

	m_animClips[enAnimationClip_Idle].Load(L"animData/player/idle.tka");
	m_animClips[enAnimationClip_Idle].SetLoopFlag(true);	
	
	m_animClips[enAnimationClip_Walk].Load(L"animData/player/walk.tka");
	m_animClips[enAnimationClip_Walk].SetLoopFlag(true);

	m_animClips[enAnimationClip_Run].Load(L"animData/player/run.tka");
	m_animClips[enAnimationClip_Run].SetLoopFlag(true);

	m_animClips[enAnimationClip_Jump].Load(L"animData/player/jump.tka");
	m_animClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animClips[enAnimationClip_Jump].SetFreezeBoneInfo(boneNo, true, true, true);	//Z���̈ړ����t���[�Y�B

	m_animClips[enAnimationClip_JumpEnd].Load(L"animData/player/jump_end.tka");
	m_animClips[enAnimationClip_JumpEnd].SetLoopFlag(false);

	m_animation.Init(m_player->GetPlayerRenderer().GetSkinModel(), m_animClips, enANimationClip_Num);
	m_currentAnimClip = enAnimationClip_Idle;
	m_animation.Play(enAnimationClip_Idle);

	m_animation.AddAnimationEventListener([&](auto clipName, auto eventName) {
		OnInvokeAnimationEvent(clipName, eventName);
	});
	//FootIK�̃p�����[�^���쐬����B
	/*CAnimationFootIK::SFootIKParam footIKParam;
	footIKParam.footBoneName_0 = L"thief_Bip01_L_Toe0";
	footIKParam.footBoneName_1 = L"thief_Bip01_R_Toe0";
	footIKParam.rootBoneName = L"thief_Bip01_Spine";
	footIKParam.footCapsuleColliderHeight_0 = UnitCM(2.0f);
	footIKParam.footCapsuleColliderHeight_1 = UnitCM(2.0f);
	footIKParam.footCapsuleColliderRadius_0 = UnitCM(1.0f);
	footIKParam.footCapsuleColliderRadius_0 = UnitCM(1.0f);
	m_animation.EnableFootIK(footIKParam);*/

	return true;
}
void CPlayerAnimator::OnChangeState(CPlayerConst::EnState nextState)
{
	//�o�^����Ă��邩������Ȃ��̂Ŕj������B
	DeleteGO(&m_jumpAnimCtr);
	if (nextState == CPlayerConst::enState_Idle) {		
		PlayAnimation(enAnimationClip_Idle, 0.2f);
	}
	else if (nextState == CPlayerConst::enState_Run)
	{
		PlayAnimation(enAnimationClip_Run, 0.2f);
	}
	else if (nextState == CPlayerConst::enState_Walk) {
		PlayAnimation(enAnimationClip_Walk, 0.2f);
	}
	else if (nextState == CPlayerConst::enState_Jump) {
		//�W�����v�̃A�j���[�V���������o�^����B
		AddGO(GetPriority(), &m_jumpAnimCtr);
	}
}
void CPlayerAnimator::Update()
{	
}