#pragma once
class Game : public IGameObject
{
public:
	////////////////////////////////////////////
	//�����o�֐��B
	////////////////////////////////////////////
	Game();
	~Game();
	/*!
	*@brief	Update�̒��O�ŌĂ΂��J�n�����B
	*@details
	* �{�֐���true��Ԃ��ƃQ�[���I�u�W�F�N�g�̏��������������Ɣ��f�����</br>
	* Update�֐����Ă΂�o���܂��Btrue��Ԃ��Ĉȍ~��Start�֐��͌Ă΂�Ȃ��Ȃ�܂��B</br>
	* �Q�[���I�u�W�F�N�g�̏������ɕ����t���[��������ꍇ�Ȃǂ�false��Ԃ��āA�������X�e�b�v�Ȃǂ��g����</br>
	* �K�؂ɏ��������s���Ă��������B
	*/
	bool Start();
	/*!
	 *@brief	�X�V�B
	 */
	void Update();
	/*!
	 *@brief	�`��B
	 */
	void Render(CRenderContext& rc);
	/*!
	*@brief	�폜�����Ƃ��ɌĂ΂��B
	*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
	* �f�X�g���N�^���O�Ɏ��s����܂��B
	*/
	virtual void OnDestroy() {}

	////////////////////////////////////////////
	//�����o�ϐ���񋓂Ƃ��B
	////////////////////////////////////////////
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enAnimationClip_walk,	//�����A�j���[�V�����B
		enAnimationClip_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	CSkinModel m_skinModel;					//�X�L�����f���B
	CSkinModelData m_skinModelData;			//�X�L�����f���f�[�^�B
	CAnimationClip m_animClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�B
	CAnimation m_animation;								//�A�j���[�V�����B
};

