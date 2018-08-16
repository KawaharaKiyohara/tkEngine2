#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 70.0f, -200.0f });
	MainCamera().Update();

	//���f���f�[�^�����[�h�B
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	
	return true;
}
void Game::Update()
{

	//�A�i���O�X�e�B�b�N�ɂ��ړ������B
	//GetLStickXF�́A�Q�[���p�b�h�̉������̓|����-1.0�`1.0��Ԃ��Ă��܂��B
	//GetLStickYF�́A�Q�[���p�b�h�̏c�����̓|����-1.0�`1.0��Ԃ��Ă��܂��B
	m_position.x += Pad(0).GetLStickXF() * 5.0f;
	m_position.z += Pad(0).GetLStickYF() * 5.0f;

	//���W��ݒ�B
	m_skinModelRender->SetPosition(m_position);
}
