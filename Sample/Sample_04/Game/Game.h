#pragma once
class Game : public IGameObject
{
public:
	////////////////////////////////////////////
	//�����o�֐��B
	////////////////////////////////////////////
	
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
	*@brief	�폜�����Ƃ��ɌĂ΂��B
	*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
	* �f�X�g���N�^���O�Ɏ��s����܂��B
	*/
	void OnDestroy();
	////////////////////////////////////////////
	//�����o�ϐ��B
	////////////////////////////////////////////
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	
	prefab::CDirectionLight* m_lig;			//���C�g�B
	CVector3 m_lightDir;					//���C�g�̕����B
};

