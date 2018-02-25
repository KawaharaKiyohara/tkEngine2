/*!
 * @brief	�Q�[���J�����B
 */

#include "stdafx.h"
#include "Camera/GameCamera.h"
#include "Player/Player.h"

namespace {
	float TARGET_OFFSET_Y = 60.0f;		//�A�N�^�[���璍���_��Y�I�t�Z�b�g�B
}
bool CGameCamera::Start()
{
	m_player = FindGO<CPlayer>("Player");
	m_springCamera.Init(MainCamera(), 500.0f, true, 5.0f);
	CVector3 toCameraPos = { 0.0f, 0.0f, 115.0f };

	CVector3 target = m_player->GetPosition();
	target.y += TARGET_OFFSET_Y;

	CVector3 pos;
	pos.Add(target, toCameraPos);

	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);
	m_springCamera.Update();

	m_toCameraPosDist = toCameraPos.Length();

	m_springCamera.SetFar(10000.0f);
	m_springCamera.SetNear(1.0f);
	m_springCamera.SetDampingRate(1.0f);


	return true;
}

void CGameCamera::Update()
{
	//�J������R�X�e�B�b�N���g���ĉ�]������B
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();
	CVector3 toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	const float CAMERA_ROT_SPEED = 2.0f;
	if (fabsf(rStick_x) > 0.0f) {
		//Y������̉�]���v�Z�B
		//��
		CMatrix mRot;
		mRot.MakeRotationY(CAMERA_ROT_SPEED * rStick_x * GameTime().GetFrameDeltaTime());
		mRot.Mul(toCameraPos);
	}
	if (fabsf(rStick_y) > 0.0f) {
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, toCameraPos);
		rotAxis.Normalize();
		CMatrix mRot;
		mRot.MakeRotationAxis(rotAxis, CAMERA_ROT_SPEED * rStick_y * GameTime().GetFrameDeltaTime());
		CVector3 toPositionOld = toCameraPos;
		mRot.Mul(toCameraPos);
		CVector3 toPosDir = toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//�J����������������B
			toCameraPos = toPositionOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������B
			toCameraPos = toPositionOld;
		}
	}

	//�V���������_���v���C���[�̍��W���猈�߂�B
	CVector3 target = m_player->GetPosition();
	target.y += TARGET_OFFSET_Y;

	if (fabsf(rStick_x) < 0.01f) {
		//R�X�e�B�b�N�̓��͂��Ȃ���΃I�[�g�J�����̏������s���B
		//���݂̃J�����ł�XZ���ʏ�ł̒����_���王�_�܂ł̃x�N�g���ƁA���̒��������߂�B
		CVector3 toCameraPosXZ = toCameraPos;
		float height = toCameraPosXZ.y;						//���_�ւ�Y�����̍����͋L�����Ă����B
		toCameraPosXZ.y = 0.0f;								//XZ���ʂɂ���̂ŁAY��0�ɂ���B
		float toCameraPosXZLen = toCameraPosXZ.Length();	//XZ���ʏ�ł̎��_�ƒ����_�̋��������߂�B
		toCameraPosXZ.Normalize();

		//XZ���ʂł̐V�����J�����̎��_�����߂�B
		//�I�[�g�J����
		toCameraPos = m_springCamera.GetPosition() - target;
		toCameraPos.y = 0.0f;
		toCameraPos.Normalize();
		//������ƂÂǔ��B
		float weight = 0.5f;	//���̃E�F�C�g�̒l��0.0�`1.0�̒l���Ƃ�B1.0�ɋ߂Â��قǒǔ��������Ȃ�B
		toCameraPos = toCameraPos * weight + toCameraPosXZ * (1.0f - weight);
		toCameraPos.Normalize();
		toCameraPos *= toCameraPosXZLen;
		toCameraPos.y = height;					//������߂��B
	}

	CVector3 pos = target + toCameraPos;	//����ŐV�������_���m��B

	//���_�ƒ����_��ݒ�B
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);


	m_springCamera.Update();
	
}