#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_charaModelRender);
	DeleteGO(m_groundModelRender);
	DeleteGO(m_sky);
	for (auto lig : m_dirLights) {
		DeleteGO(lig);
	}
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();
	LightManager().SetAmbientLight({ 0.5f, 0.5f, 0.5f });
	GraphicsEngine().GetTonemap().SetLuminance(0.38f);
	//�L�����̃����_���[�̃C���X�^���X���쐬�B�B
	m_charaModelRender = NewGO<prefab::CSkinModelRender>(0);
	//���f���f�[�^�����[�h�B
	m_charaModelRender->Init(L"modelData/unityChan.cmo");
	//�V���h�E�n�̃t���O��ݒ�B
	//�L�����̓��V�[�o�[���L���X�^�[�Ȃ̂ŃZ���t�V���h�E���ł���B
	m_charaModelRender->SetShadowCasterFlag(true);
	m_charaModelRender->SetShadowReceiverFlag(true);
	//�n�ʂ̃����_���[�̃C���X�^���X���쐬�B
	m_groundModelRender = NewGO<prefab::CSkinModelRender>(0);
	//�n�ʂ̃��f�������[�h�B
	m_groundModelRender->Init(L"modelData/bg/bg.cmo");
	//�V���h�E�n�̃t���O��ݒ�B
	//�n�ʂ̓V���h�E���V�[�o�[�B
	//�n�ʂ̓��V�[�o�[�Ȃ̂ŁA�L���X�^�[�̃I�u�W�F�N�g�̉e��������B
	m_groundModelRender->SetShadowReceiverFlag(true);
	//��̃C���X�^���X���쐬�B
	m_sky = NewGO<prefab::CSky>(0);
	
	//�f�B���N�V�������C�g��o�^�B
	auto lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetColor({ 0.8f, 0.8f, 0.8f, 1.0f });
	lig->SetDirection({ 0.0f, -0.707f, -0.707f });
	m_dirLights.push_back(lig);

	lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetColor({ 0.6f, 0.6f, 0.6f, 1.0f });
	lig->SetDirection({ 0.0f, 0.0f, -1.0f });

	m_dirLights.push_back(lig);

	//�V���h�E�}�b�v
	GraphicsEngine().GetShadowMap().SetLightDirection({ 0.0f, -0.707f, -0.707f });

	m_charaNormalMap.CreateFromDDSTextureFromFile(L"modelData/utc_normal.dds");
	m_charaSpecMap.CreateFromDDSTextureFromFile(L"modelData/utc_spec.dds");
	m_charaModelRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetNormalMap(m_charaNormalMap);
		mat->SetSpecularMap(m_charaSpecMap);
	});
	return true;
}

void Game::Update()
{
	CQuaternion qAddRot;
	qAddRot.SetRotation(CVector3::AxisY, Pad(0).GetLStickXF() * 0.1f);
	m_charaRot *= qAddRot;
	m_charaModelRender->SetRotation(m_charaRot);
}