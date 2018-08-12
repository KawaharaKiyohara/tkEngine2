#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"

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
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	
	return true;
}

void Game::Update()
{
	//CPad�̃C���X�^���X���擾�B
	CPad& pad = Pad(0);

	//���X�e�B�b�N�̓��͗ʂŃt�H���g�𓮂����B
	m_position.x += pad.GetLStickXF() * 3.0f;
	m_position.y += pad.GetLStickYF() * 3.0f;

	//�E�X�e�B�b�N�̓��͗ʂŃJ���[��ς���B
	//�J���[�͌��̎O���FRGB�ŕ\������Ă���B
	m_color.r += pad.GetRStickXF() * 0.02f;		//R�����B
	m_color.g += pad.GetRStickYF() * 0.02f;		//G�����B
	if (pad.IsPress(enButtonLeft) == true) {
		//�\���L�[�̍���������Ă�����AB���������炷�B
		m_color.b -= 0.02f;
	}
	if (pad.IsPress(enButtonRight) == true) {
		//�\���L�[�̉E��������Ă�����AR���������炷�B
		m_color.b += 0.02f;
	}
}

//�t�H���g�̕`�施�߂�IGameObject�̉��z�֐���PostRender���I�[�o�[���C�h���āA
//�����ŕ`�悷��B
void Game::PostRender(CRenderContext& rc)
{
	m_font.Begin(rc);	//�t�H���g�̕`��J�n�B
	m_font.Draw(
		L"����ɂ��͐��E",		//�\�����镶����B
		m_position,				//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		m_color
	);

	m_font.End(rc);		//�t�H���g�̕`��I���B
}