#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "GameActor.h"
#include "Background.h"
#include "GameCamera.h"
#include "Player.h"
Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�A�N�^�[�̃C���X�^���X�𐶐�����B
	m_actor = NewGO<GameActor>(0, "�ÎE��");	
	//Player���쐬�B
	m_player = NewGO<Player>(0);
	
	m_lightDir.Set(0.707f, -0.707f, 0.0f);
	m_lig = NewGO<prefab::CDirectionLight>(0);
	m_lig->SetDirection(m_lightDir);
	m_lig->SetColor({ 0.5f, 0.5f, 0.5f, 1.0f });
	LightManager().SetAmbientLight({ 0.1f, 0.1f, 0.1f });
	m_background = NewGO<Background>(0);
	m_gameCamera = NewGO<GameCamera>(0);
	return true;
}
/*!
*@brief	�폜�����Ƃ��ɌĂ΂��B
*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
* �f�X�g���N�^���O�Ɏ��s����܂��B
*/
void Game::OnDestroy()
{
	DeleteGO(m_actor);
	DeleteGO(m_background);
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
}
void Game::Update()
{
	if (GetAsyncKeyState(VK_SPACE)) {
		//�L�^���Đ�����B
		m_actor->PlayRecord();
	}
}
