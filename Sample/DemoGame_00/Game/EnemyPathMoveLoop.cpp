/*!
 * @brief	�G�̃p�X�ړ�(���[�v)�v�l�B
 */

#include "stdafx.h"
#include "EnemyPathMoveLoop.h"
#include "Path.h"
#include "Enemy.h"

EnemyPathMoveLoop::EnemyPathMoveLoop(Enemy* enemy, Path& path) :
	m_enemy(enemy),
	m_path(&path)
{
}
EnemyPathMoveLoop::~EnemyPathMoveLoop()
{
}
void EnemyPathMoveLoop::ChangeTurnState(EnState stateWhenTurnEnd, const CVector3& targetDir)
{
	//�G�l�~�[�̑O���������擾�B
	const CVector3& forward = m_enemy->GetForward();
	m_angleWhenStartTurn = atan2f(forward.x, forward.z);
	m_angleWhenEndTurn = atan2f(targetDir.x, targetDir.z);
	m_stateWhenTurnEnd = stateWhenTurnEnd;
	//�p�x�̍���180.0�ȏ�Ȃ������ׂ�B
	float diff = m_angleWhenEndTurn - m_angleWhenStartTurn;
	float diff_abs = fabsf(diff);
	if (diff_abs > CMath::PI) {
		//����180.0f�ȏ�Ȃ̂ő��肵�Ă���B
		float angle = 2.0f * CMath::PI - fabsf(diff);
		angle *= -diff / diff_abs;
		m_angleWhenEndTurn = m_angleWhenStartTurn + angle;
	}
	m_angle = m_angleWhenStartTurn;
	ChangeState(enState_Turn);
}
void EnemyPathMoveLoop::Update()
{
	float deltaTime = GameTime().GetFrameDeltaTime();
	switch (m_state) {
	case enState_FindNearEdge: {
		//�߂��G�b�W����������B
		auto* edge = m_path->GetNearEdge(m_enemy->GetPosition());
		if (edge != nullptr) {
			
			m_enemy->PlayAnimation(Enemy::enAnimationClip_run);
			m_currentEdge = edge;
			//�^�[���B
			CVector3 toEdgeVector = m_currentEdge->CalcVectorToEdge(m_enemy->GetPosition());
			toEdgeVector.y = 0.0f;
			CVector3 toEdgeVectorDir = toEdgeVector;
			toEdgeVectorDir.Normalize();
			ChangeTurnState(enState_MoveNearEdge, toEdgeVectorDir);
			
		}
	}break;
	case enState_MoveNearEdge: { //�ł��߂��G�b�W�Ɉړ�����B
		
		CVector3 toEdgeVector = m_currentEdge->CalcVectorToEdge(m_enemy->GetPosition());
		toEdgeVector.y = 0.0f;
		CVector3 toEdgeVectorDir = toEdgeVector;
		toEdgeVectorDir.Normalize();
		float move = m_enemy->MOVE_SPEED * deltaTime;
		if (toEdgeVector.Length() < m_enemy->RADIUS) {
			move = toEdgeVector.Length();
			//�������ւ̈ړ��ɐ؂�ւ��B
			//�܂��^�[��������B
			ChangeTurnState(enState_MovePath, m_currentEdge->directionXZ);
		}
		m_enemy->Move(deltaTime, toEdgeVectorDir * move / deltaTime);
		
	}break;
	case enState_MovePath: {	//�������̃p�X�ړ��B
		const PathEdge* edge = m_currentEdge;
		//�ړ��ʂ��v�Z�B
		float move = m_enemy->MOVE_SPEED * deltaTime;
		CVector3 moveSpeed = edge->directionXZ;
		moveSpeed *= move;
		//���̈ړ�����v�Z�B
		CVector3 nextPos = m_enemy->GetPosition() + moveSpeed;

		//�I�_�܂ł̋������v�Z�B
		CVector3 toEndPoint = m_currentEdge->endPos - nextPos;
		toEndPoint.y = 0.0f; //Y�͂���Ȃ��B
		if (toEndPoint.Dot(m_currentEdge->directionXZ) < 0.0f) {
			//�I�_�𒴂����B
			nextPos = m_currentEdge->endPos;
			nextPos.y = m_enemy->GetPosition().y;
			//���̃G�b�W�փS�[�B
			int nextEdgeNo = (m_currentEdge->no + 1);
			if (nextEdgeNo == m_path->GetNumEdge()) {
				//�t�����ւ̈ړ��ɐ؂�ւ��B
				ChangeTurnState(enState_MovePath_Reverse, m_currentEdge->directionXZ * -1.0f);
			}
			else {
				m_currentEdge = m_path->GetEdge(nextEdgeNo);
				//�^�[���B
				ChangeTurnState(m_state, m_currentEdge->directionXZ);
			}
		}
		m_enemy->Move(deltaTime, (nextPos-m_enemy->GetPosition()) / deltaTime);
	}break;
	case enState_MovePath_Reverse: {	//�t�����̃p�X�ړ��B
		const PathEdge* edge = m_currentEdge;
		//�ړ��ʂ��v�Z�B
		float move = m_enemy->MOVE_SPEED * GameTime().GetFrameDeltaTime();
		CVector3 moveSpeed = edge->directionXZ;
		moveSpeed *= -move;
		//���̈ړ�����v�Z�B
		CVector3 nextPos = m_enemy->GetPosition() + moveSpeed;

		//�n�_�܂ł̋������v�Z�B
		CVector3 toStartPoint = m_currentEdge->startPos - nextPos;
		toStartPoint.y = 0.0f; //Y�͂���Ȃ��B
		if (toStartPoint.Dot(m_currentEdge->directionXZ) > 0.0f) {
			//�n�_�𒴂����B
			
			CVector3 pos = m_currentEdge->startPos;
			nextPos.y = m_enemy->GetPosition().y;

			//���̃G�b�W�փS�[�B
			int nextEdgeNo = (m_currentEdge->no - 1);
			if (nextEdgeNo < 0) {
				//�������ւ̈ړ��ɐ؂�ւ��B
				//�܂��^�[��������B
				ChangeTurnState(enState_MovePath, m_currentEdge->directionXZ);
			}
			else {
				m_currentEdge = m_path->GetEdge(nextEdgeNo);
				//�^�[���B
				ChangeTurnState(m_state, m_currentEdge->directionXZ * -1.0f);
			}
		}
	
		m_enemy->Move(deltaTime, (nextPos - m_enemy->GetPosition())/ deltaTime);
	}break;
	case enState_Turn: {
		
		if (m_angleWhenStartTurn < m_angleWhenEndTurn) {
			//�������ɉ񂷁B
			m_angle = m_angle + 0.1f;
			if (m_angle > m_angleWhenEndTurn) {
				m_angle = m_angleWhenEndTurn;
				//����I���B
				ChangeState(m_stateWhenTurnEnd);
			}
		}
		else {
			//�t�����ɉ񂷁B
			m_angle = m_angle - 0.1f;
			if (m_angle < m_angleWhenEndTurn) {
				m_angle = m_angleWhenEndTurn;
				//����I���B
				ChangeState(m_stateWhenTurnEnd);
			}
		}
		CQuaternion qRot;
		qRot.SetRotation(CVector3::AxisY, m_angle);
		m_enemy->SetRotation(qRot);
		
	}break;
	}
	
}