#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "ground.h"
#include "Player.h"
#include "GameCamera.h"
#include "GameObjectName.h"
#include "StarGenerator.h"
#include "ScoreHUD.h"
#include "TimerHUD.h"
#include "Title.h"
#include "tkEngine/nature/tkSky.h"

namespace {	
	const char* GROUND_NAME = "�n��";
	const char* GAME_CAMERA_NAME = "�J����";
	const char* DIRECTION_LIG_NAME = "�f�B���N�V�������C�g";
	const char* STAR_GENERATOR_NAME = "��������";
	const char* SCORE_HUD = "�X�R�A��HUD";
	const char* TIMER_HUD_NAME = "�^�C�}�[��HUD";
	const char* SKY_NAME = "��";
}
Game::Game()
{
}


Game::~Game()
{
	DeleteGO( GROUND_NAME );
	DeleteGO( PLAYER_NAME );
	DeleteGO( GAME_CAMERA_NAME );
	DeleteGOs(DIRECTION_LIG_NAME);
	DeleteGOs(STAR_NAME);
	DeleteGO(STAR_GENERATOR_NAME);
	DeleteGO(SCORE_HUD);
	DeleteGO(m_bgm);
	DeleteGO(TIMER_HUD_NAME);
	DeleteGO(SKY_NAME);
}
bool Game::Start()
{
	auto& ge = GraphicsEngine();
	auto dirLig = NewGO<prefab::CDirectionLight>(0, DIRECTION_LIG_NAME);
	dirLig->SetDirection({ 0.0f, -0.707f, 0.707f });
	dirLig->SetColor({ 2.7f, 2.7f, 2.7f, 1.0f });
	LightManager().SetAmbientLight({ 0.4f, 0.4f, 0.4f });

	dirLig = NewGO<prefab::CDirectionLight>(0, DIRECTION_LIG_NAME);
	dirLig->SetDirection({ 0.0f, 0.707f, 0.707f });
	dirLig->SetColor({ 1.7f, 1.7f, 1.7f, 1.0f });

	dirLig = NewGO<prefab::CDirectionLight>(0, DIRECTION_LIG_NAME);
	dirLig->SetDirection({ 0.0f, 0.707f, -0.707f });
	dirLig->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });
	//
	dirLig = NewGO<prefab::CDirectionLight>(0, DIRECTION_LIG_NAME);
	dirLig->SetDirection({ 0.0f, 0.0f, 1.0f });
	dirLig->SetColor({ 0.7f, 0.7f, 0.7f, 1.0f });

	ge.GetShadowMap().SetLightDirection({0.0f, -1.0f, 0.0f});

	ge.GetPostEffect().GetTonemap().SetLuminance(0.42f);

	NewGO< Player>(0, PLAYER_NAME);
	NewGO< GameCamera>(0, GAME_CAMERA_NAME);
	NewGO<StarGenerator>(0, STAR_GENERATOR_NAME);
	NewGO< ScoreHUD>(0, SCORE_HUD);
	NewGO<TimerHUD>(0, TIMER_HUD_NAME);
	auto sky = NewGO<prefab::CSky>(0, SKY_NAME);
	sky->SetScale(8000.0f);
	sky->SetEmissionColor({ 0.2f, 0.2f, 0.2f });
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/bgm.wav");
	m_bgm->Play(false);
	m_level.Init(L"level/level_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"bg/bg") == true) {
			auto ground = NewGO<Ground>(0, GROUND_NAME);
			return true;
		}
		return false;
	});
	
	return true;
}

void Game::Update()
{
	m_restTimer = max(0.0f, m_restTimer - GameTime().GetFrameDeltaTime());
	switch (m_state) {
	case enState_Playing:
		if (m_restTimer == 0.0f) {
			//�I���B
			m_state = enState_Timeup;
		}
		break;
	case enState_Timeup:
		m_clearEffectTimer += GameTime().GetFrameDeltaTime();
		if (m_clearEffectTimer > 5.0f) {
			//5�b�o�߁B
			DeleteGO(this);
			NewGO<Title>(0);
		}
		break;
	}
	
}