#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player.h"
#include "GameCamera.h"
#include "Star.h"

Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�f�B���N�V�������C�g(���z���݂����Ȃ���)���V�[���ɒǉ��B
	m_lightDir.Set(0.707f, -0.707f, 0.0f);
	m_lig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	m_lig->SetDirection(m_lightDir);
	//���C�g�̐F��ݒ�B
	m_lig->SetColor({ 300.5f, 300.5f, 300.5f, 1.0f });

	dbg::SetDrawPhysicsCollisionEnable();
	//GameCamera�̃C���X�^���X�𐶐�����B
	m_gameCamera = NewGO<GameCamera>(0);
	//���x�����\�z����B
	m_level.Init(L"level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"star") == true) {
			
		}
		else if (objData.EqualObjectName(L"UnityChan") == true) {
			//Unity�����B
			//�v���C���[�̃C���X�^���X�𐶐�����B
			m_player = NewGO<Player>(0, "Player");
			m_player->m_position = objData.position;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		return false;
	});
	return true;
}
/*!
*@brief	�폜�����Ƃ��ɌĂ΂��B
*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
* �f�X�g���N�^���O�Ɏ��s����܂��B
*/
void Game::OnDestroy()
{
	DeleteGO("Player");
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	for (auto& star : m_starList) {
		DeleteGO(star);
	}
}
void Game::Update()
{
	if (Pad(0).IsPress(enButtonA)) {
		DeleteGO(this);
		NewGO<Game>(0);
	}
}
