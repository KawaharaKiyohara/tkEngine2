#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::OnDestroy()
{
	//�폜�B
	DeleteGO(m_directionLig);
	DeleteGO(m_charaRender);
	DeleteGO(m_bgRender);
}
/*!
*@brief	�|�C���g���C�g�̏������B
*/
void Game::InitPointLight()
{
	//�|�C���g���C�g��64�ݒu����B
	for (int i = 0; i < 100; i++) {
		//�|�C���g���C�g�𐶐��B
		prefab::CPointLight* ptLight = NewGO<prefab::CPointLight>(0);
		//�|�C���g���C�g�̍��W�������_���Ō��肷��B
		CVector3 pos;
		pos.x = CMath::Lerp((float)Random().GetRandDouble(), 200.0f, -200.0f);
		pos.y = CMath::Lerp((float)Random().GetRandDouble(), -5.0f, 0.0f);
		pos.z = CMath::Lerp((float)Random().GetRandDouble(), 200.0f, -200.0f);
		ptLight->SetPosition(pos);
		//�|�C���g���C�g�̃J���[�������_���Ō��肷��B
		CVector3 color;
		color.x = CMath::Lerp((float)Random().GetRandDouble(), 300.0f, 1000.0f);
		color.y = CMath::Lerp((float)Random().GetRandDouble(), 300.0f, 1000.0f);
		color.z = CMath::Lerp((float)Random().GetRandDouble(), 300.0f, 1000.0f);
		ptLight->SetColor(color);
		//�|�C���g���C�g�̌����p�����[�^��ݒ肷��E
		CVector3 attn = CVector3::Zero;
		attn.x = 40.0f;		//5m�܂Ō��̉e����^����B
		attn.y = 1.0f;
		ptLight->SetAttn(attn);
		//�|�C���g���C�g�̃��X�g�ɐςށB
		m_pointLightList.push_back(ptLight);

	}
}
bool Game::Start()
{
	//�f�B���N�V�������C�g(���z���݂����Ȃ���)���V�[���ɒǉ��B
	m_directionLig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	m_directionLig->SetDirection({ 0.707f, -0.707f, 0.0f });
	//���C�g�̐F��ݒ�B
	m_directionLig->SetColor({ 10.5f, 10.5f, 10.5f, 1.0f });

	//�|�C���g���C�g��ǉ��B
	InitPointLight();

	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, -10.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 50.0f, 100.0f });
	MainCamera().Update();

	//�L�����N�^�p�̃��f���f�[�^�����[�h�B
	m_charaRender = NewGO<prefab::CSkinModelRender>(0);
	m_charaRender->Init(L"modelData/Thethief_H.cmo");
	
	
	//�w�i�p�̃��f���f�[�^�����[�h�B
	m_bgRender = NewGO<prefab::CSkinModelRender>(0);
	m_bgRender->Init(L"modelData/background.cmo");
	
	
	return true;
}
void Game::Update()
{
	//�|�C���g���C�g���񂷁B
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY, 1.0f);
	for (auto& pt : m_pointLightList) {
		CVector3 pos =pt->GetPosition();
		addRot.Multiply(pos);
		pt->SetPosition(pos);
	}
	//���[���h�s����X�V�B
	m_charaRender->SetPosition({ 0.0f, -30.0f, 0.0f });
	m_charaRender->SetScale({ 2.0f, 2.0f, 2.0f });
}
