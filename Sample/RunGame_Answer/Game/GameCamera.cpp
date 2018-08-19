#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	MainCamera().SetPosition({ 0.0f, 170.0f, -500.0f});
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().Update();
	return true;
}
void GameCamera::Update()
{
	//�v���C���[�̍��W����A�����_�Ǝ��_���v�Z����B
	//�܂��̓v���C���[�̃C���X�^���X����������B
	Player* player = FindGO<Player>("�v���C���[");
	//�����_���v�Z����B
	CVector3 target = player->m_position;
	target.y += 70.0f;	//�����_�̓v���C���[�̂�����Ə�ɂ���B
	
	//�����Ď��_���v�Z����B
	CVector3 position = target;
	//���_�͒����_����y������+100�AZ������-500�ɂ���B
	position.y += 100.0f;
	position.z -= 500.0f;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肵�čX�V����B
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(position);
	MainCamera().Update();
}