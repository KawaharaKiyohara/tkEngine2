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
	virtual void OnDestroy();
	/*!
	*@brief	�|�C���g���C�g�̏������B
	*/
	void InitPointLight();
	////////////////////////////////////////////
	//�����o�ϐ��B
	////////////////////////////////////////////
	CSkinModel m_charaSkinModel;			//�L�����N�^�p�̃X�L�����f���B
	CSkinModelData m_charaSkinModelData;	//�L�����N�^�p�̃X�L�����f���f�[�^�B
	CSkinModel m_bgSkinModel;				//�w�i�p�̃L�����N�^�X�L�����f���B
	CSkinModelData m_bgSkinModelData;		//�w�i�p�̃X�L�����f���f�[�^�B

	prefab::CDirectionLight* m_directionLig = nullptr;		//�f�B���N�V�������C�g�B
	std::vector<prefab::CPointLight*>	m_pointLightList;	//�|�C���g���C�g�̃��X�g�B
};

