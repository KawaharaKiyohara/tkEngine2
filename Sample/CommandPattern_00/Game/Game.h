#pragma once

class GameActor;
class Background;
class GameCamera;
class NPC;
class Player;
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
	*@brief	�폜�����Ƃ��ɌĂ΂��B
	*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
	* �f�X�g���N�^���O�Ɏ��s����܂��B
	*/
	void OnDestroy();
	////////////////////////////////////////////
	//�����o�ϐ��B
	////////////////////////////////////////////
	prefab::CDirectionLight* m_lig;			//���C�g�B
	CVector3 m_lightDir;					//���C�g�̕����B
	GameActor* m_actor = nullptr;			//�A�N�^�[�B
	Background* m_background = nullptr;		//�w�i�B
	GameCamera* m_gameCamera = nullptr;		//�Q�[���J�����B
	NPC* m_npc = nullptr;					//NPC
	Player* m_player = nullptr;				//Player

};

