/*!
 * @brief	�G�l�~�[�B
 */

#pragma once

#include "tkEngine/graphics/tkSkinModelRender.h"

class Enemy : public IGameObject{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	Enemy();
	/*!
	 * @brief	�f�X�g���N�^�B��
	 */
	~Enemy();
	/*!
	 * @brief	�X�^�[�g�B
	 */
	bool Start() override;
	/*!
	 * @brief	�X�V�B
	 */
	void Update() override;
	
	/*!
	 *@brief	���W��ݒ�B
	 */
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enANimationClip_Num,
	};
	EnAnimationClip m_currentAnimClip = enAnimationClip_Idle;	//!<���ݍĐ����̃A�j���[�V�����N���b�v�B
	CAnimationClip m_animClips[enANimationClip_Num];			//!<�A�j���[�V�����N���b�v�G�B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//!<�X�L�����f�������_���[�B
	CVector3		m_position;									//!<���W�B
	CQuaternion		m_rotation = CQuaternion::Identity;			//!<��]�B
};