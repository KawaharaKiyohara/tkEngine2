#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("Player");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	m_springCamera.Init(MainCamera(), 1200.0f, false, 20.0f);
	return true;
}
void GameCamera::Update()
{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
	if (m_isDebugCamera) {
		float debugCameraSpeed = 8.0f;
		if (Pad(0).IsPress(enButtonUp) ){
			if (Pad(0).IsPress(enButtonRB2)) {
				MainCamera().m_debugCameraPosition.y += debugCameraSpeed;
				MainCamera().m_debugCameraTarget.y += debugCameraSpeed;
			}
			else {
				MainCamera().m_debugCameraPosition += MainCamera().GetForward() * debugCameraSpeed;
				MainCamera().m_debugCameraTarget += MainCamera().GetForward() * debugCameraSpeed;
			}
		}
		if (Pad(0).IsPress(enButtonDown)) {
			if (Pad(0).IsPress(enButtonRB2)) {
				MainCamera().m_debugCameraPosition.y -= debugCameraSpeed;
				MainCamera().m_debugCameraTarget.y -= debugCameraSpeed;
			}
			else {
				MainCamera().m_debugCameraPosition += MainCamera().GetForward() * -debugCameraSpeed;
				MainCamera().m_debugCameraTarget += MainCamera().GetForward() * -debugCameraSpeed;
			}
		}
		if (Pad(0).IsPress(enButtonRight)) {
			MainCamera().m_debugCameraPosition += MainCamera().GetRight() * debugCameraSpeed;
			MainCamera().m_debugCameraTarget += MainCamera().GetRight() * debugCameraSpeed;
		}
		if (Pad(0).IsPress(enButtonLeft)) {
			MainCamera().m_debugCameraPosition += MainCamera().GetRight() * -debugCameraSpeed;
			MainCamera().m_debugCameraTarget += MainCamera().GetRight() * -debugCameraSpeed;
		}
		MainCamera().Update();
		return;
	}
	else {
		if (Pad(0).IsPress(enButtonStart)
			&& Pad(0).IsPress(enButtonDown)) {
			MainCamera().m_isDebugCamera = true;
			MainCamera().m_debugCameraPosition = MainCamera().GetPosition();
			MainCamera().m_debugCameraTarget = MainCamera().GetTarget();
			m_isDebugCamera = true;
		}
	}
#endif
	//�J�������X�V�B
	//�����_���v�Z����B
	CVector3 target = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 50.0f;
	//���_���v�Z����B
	CVector3 toPos = { 0.0f, 350.0f, 550.0f };
	CVector3 pos = target + toPos;	//�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���B
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}
void GameCamera::NotifyGameOver()
{
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}
void GameCamera::NotifyRestart()
{
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = true;
}
void GameCamera::NotifyGameClear()
{
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}