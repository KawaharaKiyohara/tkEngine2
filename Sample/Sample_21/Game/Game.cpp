#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_directionLight);
	DeleteGO(m_unityChanModelRender);
	DeleteGO(m_bgModelRender);
	DeleteGO(m_starModelRender);
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 200.0f, 500.0f });
	MainCamera().Update();

	//���C�g����{�ǉ��B
	m_directionLight = NewGO<prefab::CDirectionLight>(0);
	m_directionLight->SetDirection({ 0.707f, -0.707f, 0.0f });
	m_directionLight->SetColor({2.0f, 2.0f, 2.0f, 1.0f});

	//���j�e�B�����̃X�L�����f�������_���[���쐬�B
	m_unityChanModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_unityChanModelRender->Init(L"modelData/unityChan.cmo");
	m_unityChanModelRender->SetShadowCasterFlag(true);
	//�w�i���f���̃����_���[���쐬�B
	m_bgModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_bgModelRender->Init(L"modelData/bg/bg.cmo");
	m_bgModelRender->SetShadowReceiverFlag(true);
	//���̃��f���̃����_���[���쐬����B
	m_starModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_starModelRender->Init(L"modelData/star/star.cmo");
	m_starModelRender->SetScale({ 20.0f, 20.0f, 20.0f });
	CVector3 starPos = { 0.0f, 200.0f, 0.0f };
	m_starModelRender->SetPosition(starPos);

	//�S���ʃ��C�g��ݒ肷��B
	//���C�g�̍��W��ݒ肷��B
	shadow::OminiDirectionShadowMap().SetLightPosition(starPos);
	//�S���ʃV���h�E�̉e���͈͂�ݒ肷��B
	shadow::OminiDirectionShadowMap().SetDistanceAffectedByLight(1000);

	//�S���ʃV���h�E�̌��ʂ𕪂���₷�����邽�߂ɁA�w�����V���h�E�͖����ɂ��Ă����B
	shadow::DirectionShadowMap().Disable();
	return true;
}
void Game::Update()
{
	//�Q�[���p�b�h�̓��͂�Unity�����𓮂����B
	m_unityChanPosition.x -= Pad(0).GetLStickXF() * 5.0f;
	m_unityChanPosition.z -= Pad(0).GetLStickYF() * 5.0f;
	m_unityChanModelRender->SetPosition(m_unityChanPosition);
}

