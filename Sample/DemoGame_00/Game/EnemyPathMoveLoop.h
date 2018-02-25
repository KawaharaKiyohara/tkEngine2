/*!
 * @brief	�G�̃p�X�ړ�(���[�v)�v�l�B
 */

#pragma once


class Enemy;
class PathEdge;
class Path;
/*!
 * @brief	�p�X�ړ�(���[�v)�v�l�B
 */
class EnemyPathMoveLoop
{
private:
	enum EnState {
		enState_FindNearEdge,		//�߂��G�b�W�������B
		enState_MoveNearEdge,		//�߂��G�b�W�Ɉړ��B
		enState_MovePath,			//�p�X���ړ��B
		enState_MovePath_Reverse,	//�p�X���t�����Ɉړ����B�B
		enState_Turn,		//���̃G�b�W�Ɍ����Đ���B

	};
public:
	EnemyPathMoveLoop(Enemy* enemy, Path& path);
	~EnemyPathMoveLoop();
	void Update();
private:
	/*!
	 *@brief	��Ԑ؂�ւ��B
	 */
	void ChangeState(EnState nextState)
	{
		m_state = nextState;
	}
	/*!
	*@brief	�^�[����Ԃɐ؂�ւ���Ƃ��͂��������g���B
	*@param[in]	stateWhenTurnEnd	�^�[���I�����̎��̃X�e�[�g�B
	*@param[in]	turnDir				�ړI�i�s�����B
	*/
	void ChangeTurnState(EnState stateWhenTurnEnd, const CVector3& targetDir);

private:
	
	const PathEdge* m_currentEdge = nullptr;
	Enemy*	m_enemy = nullptr;
	Path* m_path = nullptr;
	EnState m_state = enState_FindNearEdge;
	EnState m_stateWhenTurnEnd;				//!<�^�[���I�����̎��̃X�e�[�g�B	
	float m_angleWhenStartTurn;				//!<�^�[���J�n���̃A���O���B�P�ʁF���W�A���B
	float m_angleWhenEndTurn;				//!<�^�[���I�����̃A���O���B�P�ʁF���W�A���B
	float m_angle = 0.0f;					//!<�^�[�����̊p�x�B
	
	
};