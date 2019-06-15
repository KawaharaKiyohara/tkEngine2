#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_charaModelRender);
	DeleteGO(m_groundModelRender);
	DeleteGO(m_sky);
	DeleteGO(m_starModelRender);
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
	//���̃����_���[�̃C���X�^���X���쐬�B
	m_starModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_starModelRender->Init(L"modelData/star/star.cmo");
	m_starModelRender->SetScale({ 20.0f, 20.0f, 20.0f });
	m_starModelRender->SetPosition({ -150.0f, 50.0f, -50.0f });
	m_starModelRender->SetShadowCasterFlag(true);
	m_starModelRender->SetShadowReceiverFlag(true);
	//���Ȕ����J���[��ݒ�B
	m_starModelRender->SetEmissionColor({ 0.8f, 0.8f, 0.0f });
	m_starLight = NewGO<prefab::CPointLight>(0);
	m_starLight->SetPosition({ -150.0f, 50.0f, -50.0f });
	m_starLight->SetAttn({ 200.0f, 2.0f, 0.0f });
	m_starLight->SetColor({ 10.0f, 10.0f, 0.0f });
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
	shadow::DirectionShadowMap().SetLightDirection({ 0.0f, -0.707f, -0.707f });

	m_charaNormalMap.CreateFromDDSTextureFromFile(L"modelData/utc_normal.dds");
	m_charaSpecMap.CreateFromDDSTextureFromFile(L"modelData/utc_spec.dds");
	m_charaModelRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetNormalMap(m_charaNormalMap);
		mat->SetSpecularMap(m_charaSpecMap);
	});
	m_groundSpecMap.CreateFromDDSTextureFromFile(L"modelData/bg/bgSpec.dds");
	m_groundModelRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetSpecularMap(m_groundSpecMap);
	});
	return true;
}

void Game::Update()
{
	auto dt = GameTime().GetFrameDeltaTime();
	CQuaternion qAddRot;
	qAddRot.SetRotation(CVector3::AxisY, Pad(0).GetRStickXF() * 4.0f * dt);
	m_charaRot *= qAddRot;
	m_charaModelRender->SetRotation(m_charaRot);

	m_charaPos.x += Pad(0).GetLStickXF() * -400.0f * dt;
	m_charaPos.z += Pad(0).GetLStickYF() * -400.0f * dt;
	m_charaModelRender->SetPosition(m_charaPos);

	qAddRot.SetRotation(CVector3::AxisY, 4.0f * dt);
	m_starRot *= qAddRot;
	m_starModelRender->SetRotation(m_starRot);
	auto pos = m_charaPos;
	pos.y += 50.0f;
	MainCamera().SetTarget(pos);
	auto target = pos;
	target.z += 300.0f;
	MainCamera().SetPosition(target);
	MainCamera().Update();
}