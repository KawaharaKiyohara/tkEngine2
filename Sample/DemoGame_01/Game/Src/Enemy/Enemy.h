/*!
 * @brief	�G�l�~�[�B
 */

#pragma once

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
	 * @brief	�`��
	 *@param[in]	rc		�����_�����O�R���e�L�X�g�B
	 */
	void Render(CRenderContext& rc) override;
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
	EnAnimationClip m_currentAnimClip = enAnimationClip_Idle;		//!<���ݍĐ����̃A�j���[�V�����N���b�v�B
	CAnimationClip m_animClips[enANimationClip_Num];	//!<�A�j���[�V�����N���b�v�G�B
	CAnimation m_animation;								//!<�A�j���[�V�����B
	CSkinModelData	m_skinModelData;	//!<�X�L�����f���f�[�^�B
	CSkinModel		m_skinModel;		//!<�X�L�����f���B
	CVector3		m_position;			//!<���W�B
	CQuaternion		m_rotation;			//!<��]�B
};