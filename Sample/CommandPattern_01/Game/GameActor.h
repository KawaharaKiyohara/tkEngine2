#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"
class ICommand;
class GameActor : public IGameObject
{
private:

	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enAnimationClip_walk,	//�����A�j���[�V�����B
		enAnimationClip_num,	//�A�j���[�V�����N���b�v�̑����B
	};
public:
	GameActor();
	~GameActor();
	void Update();
	void Render(CRenderContext& rc);
	bool Start();

	
	/*!
	 *@brief	�����B
	 */
	void Walk(CVector3 move);
	
	/*!
	 *@brief	���W���擾�B
	 */
	CVector3 GetPosition() const
	{
		return m_position;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(pos);
	}
	/*!
	 *@brief	���߂�ǉ��B
	 */
	void AddCommand(ICommand* command)
	{
		m_commands.push_back(command);
		m_commandsRecord.push_back(command);	//����͂��܂��C�ɂ��Ȃ��Ă����B
	}
	/*!
	 *@brief	���R�[�h�̍Đ��J�n�B
	 *@details
	 * �I�}�P�I�}�P�B
	 */
	void PlayRecord()
	{
		//�S�������l�ɖ߂��B
		m_moveSpeedDown = CVector3::Zero;
		m_position = CVector3::Zero;
		m_rotation = CQuaternion::Identity;
		m_moveDir = CVector3::Back;
		m_charaCon.SetPosition(m_position);
		//���R�[�h�Đ����̂𗧂Ă�B
		m_isPlayRecord = true;
	}
	bool IsPlayRecord() const
	{
		return m_isPlayRecord;
	}
private:
	//�A�j���[�V�������������B
	void InitAnimation();
	/*!
	 *@brief	�A�j���[�V�������Đ��B
	 */
	void PlayAnimation(EnAnimationClip nextClip)
	{
		if (m_currentAnimationClip != nextClip) {
			m_animation.Play(nextClip, 0.2f);
			m_currentAnimationClip = nextClip;
		}
	}
	/*!
	 *@brief	�R�}���h�����s�B
	 */
	void ExecuteCommand();
	/*!
	 *@brief	���R�[�h���Đ��B
	 */
	void ExecuteRecord();
private:
	
	EnAnimationClip				m_currentAnimationClip;		//���݂̃A�j���[�V�����N���b�v�B
	CAnimationClip				m_animationClip[enAnimationClip_num];	//�A�j���[�V�����N���b�v�B
	CAnimation					m_animation;				//�A�j���[�V�����B
	CSkinModelData				m_skinModelData;			//�X�L�����f���f�[�^�B
	CSkinModel					m_skinModel;				//�X�L�����f���B
	CVector3					m_position = CVector3::Zero;	//���W�B
	CQuaternion					m_rotation = CQuaternion::Identity;	//��]�B
	CCharacterController		m_charaCon;					//�L�����N�^�[�R���g���[���[�B
	CVector3					m_moveDir = CVector3::Back;	//�i�s�����B
	prefab::CDirectionLight*	m_directionLig = nullptr;
	CShaderResourceView			m_normalMapSRV;				//!<�@���}�b�v��SRV�B
	CShaderResourceView			m_specularMapSRV;			//!<�X�y�L�����}�b�v��SRV�B
	CShaderResourceView			m_wnormalMapSRV;			//!<����̖@���}�b�v��SRV�B
	CShaderResourceView			m_wspecularMapSRV;			//!<����̃X�y�L�����}�b�v��SRV�B
	CVector3					m_moveSpeedDown = CVector3::Zero;
	std::deque<ICommand*>		m_commands;					//!<���߃��X�g�B

	///////////////////////////////////////////////////////////////////////
	// �I�}�P����B
	///////////////////////////////////////////////////////////////////////
	bool						m_isPlayRecord;
	std::deque<ICommand*>		m_commandsRecord;			//!<�S�R�}���h�̋L�^�B
};

