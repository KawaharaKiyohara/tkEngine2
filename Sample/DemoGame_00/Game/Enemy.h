#pragma once

#include "Path.h"
#include "EnemyPathMoveLoop.h"
#include "tkEngine/character/tkCharacterController.h"

class Player;
class Game;
class Enemy : public IGameObject
{
public:
	const float MOVE_SPEED = 150.0f;
	const float RADIUS = 20.0f;
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_num,
	};
	Enemy();
	~Enemy();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	/*!
	 *@brief	���W�̎擾�B
	 */
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
	 *@brief	���W�̐ݒ�B
	 */
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	 *@brief	�������B
	 */
	void Init(const wchar_t* movePathFilePath)
	{
		m_movePath.Load(movePathFilePath);
	}
	/*!
	 *@brief	��]��ݒ�B
	 */
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/*!
	 *@brief	�A�j���[�V�������Đ��B
	 *@param[in]	animNo		�A�j���[�V�����ԍ��B
	 */
	void PlayAnimation(EnAnimationClip animNo)
	{
		m_animation.Play(animNo);
	}
	void Move(float deltaTime, CVector3 move)
	{
		m_position = m_charaCon.Execute(deltaTime, move);
	}
	/*!
	 *@brief	�G�̑O�������擾�B
	 */
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
	 *@brief	�v���C���[�𔭌�����������B
	 */
	bool IsFindPlayer() const
	{
		return m_isFindPlayer;
	}
	/*!
	 *@brief	���X�^�[�g��ʒm�B
	 */
	void NotifyRestart();
private:
	/*!
	 *@brief	�v���C���[�����G
	 */
	void SearchPlayer();
private:
	
	
	CSkinModelData m_skinModelData;					//!<�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;							//!<�X�L�����f���B
	CAnimationClip m_animClip[enAnimationClip_num];	//!<�A�j���[�V�����N���b�v�B
	CAnimation m_animation;							//!<�A�j���[�V�����B
	CVector3 m_position = CVector3::Zero;			//!<���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//!<��]�B
	Path m_movePath;								//!<�ړ��p�X�B
	EnemyPathMoveLoop m_pathMoveLoop;				//!<�p�X�̃��[�v�ړ��v�l�B
	CCharacterController m_charaCon;				//!<�L�����N�^�R���g���[���B
	CVector3 m_forward = CVector3::AxisZ;			//!<�G�l�~�[�̑O�������B
	Player* m_player = nullptr;						//!<�v���C���[�B
	Game* m_game = nullptr;
	bool m_isFindPlayer = false;					//!<�v���C���[�𔭌��B
};

