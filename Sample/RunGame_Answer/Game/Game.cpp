#include "stdafx.h"
#include "Game.h"
#include "Title.h"


Game::Game()
{
	//�R���X�g���N�^�̓C���X�^���X���������ꂽ�Ƃ���
	//�����I�ɌĂ΂�����Ȋ֐��B
	m_gameCamera = NewGO<GameCamera>(0);	//��Ŕj������̂ŁAGameCamera�̃C���X�^���X�������o�ϐ��ɋL�����Ă����B
	m_player = NewGO<Player>(0, "�v���C���[");	//��Ŕj������̂ŁAPlayer�̃C���X�^���X�������o�ϐ��ɋL�����Ă����B
	m_background = NewGO<Background>(0);

	//��ڂ�Star���쐬����B
	m_star[0] = NewGO<Star>(0, "�����[");
	m_star[0]->m_position.x = 200.0f;
	m_star[0]->m_position.y = 0.0f;
	m_star[0]->m_position.z = 0.0f;

	//��ڂ�Star���쐬����B
	m_star[1] = NewGO<Star>(0, "�����[");
	m_star[1]->m_position.x = 400.0f;
	m_star[1]->m_position.y = 0.0f;
	m_star[1]->m_position.z = 0.0f;

	//�O�ڂ�Star���쐬����B
	m_star[2] = NewGO<Star>(0, "�����[");
	m_star[2]->m_position.x = 600.0f;
	m_star[2]->m_position.y = 0.0f;
	m_star[2]->m_position.z = 0.0f;

	//�l�ڂ�Star���쐬����B
	m_star[3] = NewGO<Star>(0, "�����[");
	m_star[3]->m_position.x = 800.0f;
	m_star[3]->m_position.y = 0.0f;
	m_star[3]->m_position.z = 0.0f;

	//�܂ڂ�Star���쐬����B
	m_star[4] = NewGO<Star>(0, "�����[");
	m_star[4]->m_position.x = 1000.0f;
	m_star[4]->m_position.y = 200.0f;
	m_star[4]->m_position.z = 0.0f;
}

Game::~Game()
{
	//�R���X�g���N�^�̓C���X�^���X���j�����ꂽ�Ƃ���
	//�����I�ɌĂ΂�����Ȋ֐��B
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_background);
	
	//Star�̃C���X�^���X��j������B
	for (int i = 0; i < 5; i++) {
		DeleteGO( m_star[i] );
	}
	DeleteGO(m_clearSpriteRender);
}
void Game::Update()
{
	if (m_isClear == false) {
		//�N���A���Ă��Ȃ��Ƃ��̏���
		if (Pad(0).IsPress(enButtonSelect) == true) {
			//�Z���N�g�{�^���������ꂽ�B
			//Title�N���X�̃C���X�^���X�𐶐��B
			//�����Title�N���X�̃R���X�g���N�^���Ă΂��B
			NewGO<Title>(0);
			//Game�N���X�̃C���X�^���X��j���B
			//�����Game�N���X�̃f�X�g���N�^���Ă΂��B
			DeleteGO(this);
		}
		if (m_numGetStarCount == 5) {
			//����5���낦���̂ŁA�N���A�t���O�𗧂ĂāA
			//�Q�[���N���A�Q�c��\������X�v���C�g�����_���[���쐬����B
			m_isClear = true;
			m_clearSpriteRender = NewGO<prefab::CSpriteRender>(0);
			m_clearSpriteRender->Init(L"sprite/GAMECLEAR.dds", 712, 65);
		}
	}
	else {
		//�N���A���Ă���B
		m_timer++;
		if (m_timer == 60) {
			//60�t���[���o�߂�����^�C�g����ʂɖ߂�B
			NewGO<Title>(0);
			DeleteGO(this);
		}
	}
}
