#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:
	
	void OnDestroy() override;
	void Update() override;
	bool Start() override;	
	//�ړ������B
	void Move();
	void Turn();
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
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;	//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	
	CShaderResourceView	m_normalMapSRV;			//!<�@���}�b�v��SRV�B
	CShaderResourceView m_specularMapSRV;		//!<�X�y�L�����}�b�v��SRV�B
	CShaderResourceView	m_wnormalMapSRV;		//!<����̖@���}�b�v��SRV�B
	CShaderResourceView m_wspecularMapSRV;		//!<����̃X�y�L�����}�b�v��SRV�B
};

