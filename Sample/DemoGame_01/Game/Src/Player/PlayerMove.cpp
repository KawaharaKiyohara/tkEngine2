/*!
 * @brief	�v���C���[�̈ړ������B
 */
#include "stdafx.h"
#include "Player/Player.h"
#include "Player/PlayerMove.h"
#include "Camera/GameCamera.h"


CPlayerMove::CPlayerMove(CPlayer* pl) :
	m_player(pl)
{
}
CPlayerMove::~CPlayerMove()
{
}
bool CPlayerMove::Start()
{
	m_charaCon.Init(15.0f, 50.0f, m_player->GetPosition());
	m_gameCamera = FindGO<CGameCamera>("GameCamera");
	//�X�e�[�g�؂�ւ��̃��X�i�[��o�^�B
	m_player->AddChangeStateListner([&](CPlayerConst::EnState nextState) {
		OnChangeState(nextState);
	});
	return true;
}
void CPlayerMove::OnChangeState(CPlayerConst::EnState nextState)
{
	(void)nextState;
}
void CPlayerMove::Update()
{
	//XZ���ʂł̈ړ��͑ł������B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	if (m_player->IsPossibleMove() == false) {
		//�ړ��ł��Ȃ��B
		m_accelTime = 0.0f;
		return;
	}
	
	float lx = Pad(0).GetLStickXF();
	float ly = Pad(0).GetLStickYF();
	
	if (fabsf(lx) < 0.01f && fabsf(ly) < 0.01f) {
		m_accelTime = 0.0f;
	}
	m_accelTime = min(m_accelTime + 5.0f * GameTime().GetFrameDeltaTime(), 1.0f);

	CVector3 forward = MainCamera().GetForward();
	forward.y = 0.0f;	//Y����Ȃ��B
	forward.Normalize();
	forward.Scale(ly * CPlayerConst::RUN_SPEED * m_accelTime);
	CVector3 right = MainCamera().GetRight();
	right.y = 0.0f;		//Y����Ȃ��B
	right.Normalize();
	right.Scale(lx * CPlayerConst::RUN_SPEED * m_accelTime);

	
	//���̃t���[���̈ړ����x���v�Z����B
	//�܂���XZ���ʂł̈ړ����x�B
	CVector3 moveSpeed;
	moveSpeed = forward + right;
#if 1 //@todo for footIKTest
	if (m_player->IsApplyGravity()) {
		//������Y�����B
		float addYSpeed = -980.0f * GameTime().GetFrameDeltaTime();	//�d�͂ɂ�鑬�x�������v�Z�B
		moveSpeed.y = m_moveSpeed.y + addYSpeed;
	}
#endif
	//�v�Z�I���B
	m_moveSpeed = moveSpeed + m_addMoveSpeed;
	
#if 1 //@todo for footIKTest
	//�v�Z���ꂽ�ړ����x���g���Ĉړ�������B
	CVector3 pos = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
#else
	CVector3 pos = m_player->GetPosition();
	pos += m_moveSpeed * GameTime().GetFrameDeltaTime();
#endif
	m_player->SetPosition(pos);
	
	//�O��������Z����Ă���͂��N���A����B
	m_addMoveSpeed = CVector3::Zero;	
}