#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(CRenderContext& rc);
	bool Start();

	//�A�j���[�V�������������B
	void InitAnimation();
	//�A�j���[�V��������B
	void AnimationControl();
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enAnimationClip_walk,	//�����A�j���[�V�����B
		enAnimationClip_num,	//�A�j���[�V�����N���b�v�̑����B
	};
	CAnimationClip m_animationClip[enAnimationClip_num];	//�A�j���[�V�����N���b�v�B
	CAnimation m_animation;			//�A�j���[�V�����B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;			//�X�L�����f���B
	CVector3 m_position = CVector3::Zero;	//���W�B

	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
};

