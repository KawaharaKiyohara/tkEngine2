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
	
	return true;
}
/*!
*@brief	�폜�����Ƃ��ɌĂ΂��B
*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
* �f�X�g���N�^���O�Ɏ��s����܂��B
*/
void Game::OnDestroy()
{
	//�T�E���h�\�[�X�̃C���X�^���X��j�������BGM�͒�~����B
	DeleteGO(m_bgmSoundSource);
}
void Game::Update()
{
	prefab::CSoundSource* ss;
	if (Pad(0).IsTrigger(enButtonA)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/PlayerAttack_00.wav");
		ss->Play(false);	//���[�v�t���O��false�ɐݒ肵�čĐ�����ƁA
							//�Đ����I�������CSoundSourcen�̃C���X�^���X�͎����I�ɍ폜�����̂�
							//�C���X�^���X�������o�ϐ��Ȃǂŕێ�����K�v�͂Ȃ�
		//�����V���b�g�Đ��̏I�������o�������ꍇ�̓C�x���g���X�i�[�ɓo�^���s���΂悢�B
		ss->AddEventListener([](SEventParam& eventParam) {
			if (eventParam.eEvent == IGameObject::enEvent_Destroy) {
				MessageBox(NULL, "PlayerAttack_01.wav�̍Đ�����", "�ʒm", MB_OK);
			}
		});
	}
	else if (Pad(0).IsTrigger(enButtonB)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/PlayerAttack_01.wav");
		ss->Play(false);
		
	}else if (Pad(0).IsTrigger(enButtonX)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/PlayerDead.wav");
		ss->Play(false);
	}
	else if (Pad(0).IsTrigger(enButtonY)) {
		if (m_bgmSoundSource == nullptr) {
			//BGM�𗬂��Ă��Ȃ��B
			//�T�E���h�\�[�X���쐬�B
			m_bgmSoundSource = NewGO<prefab::CSoundSource>(0);
			//�������B
			m_bgmSoundSource->Init(L"sound/bgm.wav");
			//���[�v�t���O��true�ɂ��čĐ����Ă���̂ŁA
			//�����~�߂�Ƃ��͖����I�ɃC���X�^���X��j������K�v������B
			m_bgmSoundSource->Play(true);
		}
		else {
			//BGM���폜�B
			DeleteGO(m_bgmSoundSource);
			m_bgmSoundSource = nullptr;
		}
	}
}
