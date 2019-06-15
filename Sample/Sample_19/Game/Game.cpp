#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

Game::Game()
{

}
Game::~Game()
{
	DeleteGO(m_backGroundRender);
	DeleteGO(m_playerRender);
	DeleteGO(m_pointLig);
}
bool Game::Start()
{
	//�J�������������B
	InitCamera();
	//�X�L�����f�������_���[���������B
	InitSkinModelRender();
	//�S�[�X�g�̏������B
	InitGhostObject();

	m_charaCon.Init(30.0f, 100.0f, CVector3::Zero);
	//�|�C���g���C�g���쐬�B
	m_pointLig = NewGO<prefab::CPointLight>(0);
	m_pointLig->SetPosition({ -727.52f, 500.0f, 29.45f });
	m_pointLig->SetColor({ 100.0f, 0.0f, 0.0f });
	m_pointLig->SetAttn({ 800.f, 10.0f, 0.0f });
	m_pointLig->SetActiveFlag(false); //��A�N�e�B�u�ɂ��Ă����B
	return true;
}
void Game::InitSkinModelRender()
{
	m_backGroundRender = NewGO<prefab::CSkinModelRender>(0);
	m_backGroundRender->Init(L"modelData/background/background.cmo");

	m_playerRender = NewGO<prefab::CSkinModelRender>(0);
	m_playerRender->Init(L"modelData/player/unityChan.cmo");
}
void Game::InitCamera()
{
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 570.0f, 1000.0f });
	MainCamera().Update();
}
void Game::InitGhostObject()
{
	//�S�[�X�g�̃��C���[�t���[���\����L���ɂ���B
	PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_ghostObject.CreateBox(
		{ -500.0f, 100.0f, 0.0f },	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{200.0f, 200.0f, 200.0f}	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
}

void Game::Update()
{
	//�p�b�h�̓��͂ŃL�����𓮂����B
	CVector3 moveSpeed;
	moveSpeed.x = Pad(0).GetLStickXF() * -300.0f;
	moveSpeed.y = 0.0f;
	moveSpeed.z = Pad(0).GetLStickYF() * -300.0f;
	//moveSpeed�ɐݒ肳�ꂽ���x�ŁA�L�����N�^�[�𓮂����B
	m_charaCon.Execute(moveSpeed);
	//�L�����R���œ����������ʂ�CSkinModelRender�ɔ��f������B
	m_playerRender->SetPosition(m_charaCon.GetPosition());

	m_pointLig->SetActiveFlag(false); //��A�N�e�B�u�ɂ��Ă����B
	//�L�����N�^�[�ƃS�[�X�g�̂����蔻����s���B
	PhysicsWorld().ContactTest(m_charaCon,	[&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObject�ƂԂ�����
			m_pointLig->SetActiveFlag(true);	//�|�C���g���C�g������B
		}
	});
}