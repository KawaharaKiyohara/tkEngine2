#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Background.h"
#include "Ball.h"

namespace {
	const char* cDIR_LIGHT_NAME = "dirLight";
	const char* cBG_NAME = "�w�i";
	const char* cBALL_NAME = "�{�[��";
}
Game::Game()
{
}


Game::~Game()
{
	//�Q�[���I�u�W�F�N�g�𖼑O�w��ō폜�B
	DeleteGOs(cDIR_LIGHT_NAME);
	DeleteGOs(cBG_NAME);
}
void Game::InitLight()
{
	auto dirLight = NewGO<prefab::CDirectionLight>(0, cDIR_LIGHT_NAME);
	dirLight->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	auto lightDir = CVector3(1, -1, 1);
	lightDir.Normalize();
	dirLight->SetDirection(lightDir);
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);

	dirLight = NewGO<prefab::CDirectionLight>(0, cDIR_LIGHT_NAME);
	dirLight->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	dirLight->SetDirection({ 0.0f, -0.707f, 0.707f });

	dirLight = NewGO<prefab::CDirectionLight>(0, cDIR_LIGHT_NAME);
	dirLight->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	dirLight->SetDirection({ 0.0f, -0.707f, -0.707f });

	dirLight = NewGO<prefab::CDirectionLight>(0, cDIR_LIGHT_NAME);
	dirLight->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	dirLight->SetDirection({ 0.707f, -0.707f, 0.0f });
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 0.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 300.0f, 300.0f });
	MainCamera().Update();
	
	dbg::SetDrawPhysicsCollisionEnable();
	//�����G���W���̏d�͂�ݒ肷��B
	PhysicsWorld().SetGravity({ 0.0f, -980.0f, 0.0f });
	//���C�g���������B	
	InitLight();
	//�w�i���쐬�B
	NewGO<Background>(0, cBG_NAME);
	NewGO<Ball>(0, cBALL_NAME);
	return true;
}

void Game::Update()
{
}