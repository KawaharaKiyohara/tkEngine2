#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "Game.h"

Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/star/star.cmo");
	
	//����x���W�̍ő���W�ƍŏ����W�B
	const float STAR_X_POS_MAX = 1000.0f;
	const float STAR_X_POS_MIN = -1000.0f;
	//����z���W�̍ő���W�ƍŏ����W�B
	const float STAR_Z_POS_MAX = 1000.0f;
	const float STAR_Z_POS_MIN = -1000.0f;
	//���̊J�n����Y���W�B
	const float STAR_START_Y_POS = 1000.0f;
	//���W�������_���ɏ���������B
	
	//y�͌Œ�B
	m_position.y = STAR_START_Y_POS;
	//x��z�������_���ɏ���������B
	auto& rnd = Random();
	m_position.x = CMath::Lerp(rnd.GetRandDouble(), STAR_X_POS_MIN, STAR_X_POS_MAX);
	m_position.z = CMath::Lerp(rnd.GetRandDouble(), STAR_Z_POS_MIN, STAR_Z_POS_MAX);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale({ 40.0f, 40.0f, 40.0f });
	m_skinModelRender->SetShadowCasterFlag(true);
	m_player = FindGO<Player>(PLAYER_NAME);
	m_game = FindGO<Game>(GAME_NAME);
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
}

void Star::Update()
{
	//�����������鑬�x�B�P��(cm/sec)
	const float STAR_FALL_SPEED = 200.0f;
	m_position.y -= STAR_FALL_SPEED * GameTime().GetFrameDeltaTime();
	m_skinModelRender->SetPosition(m_position);
	CQuaternion qAddRot;
	qAddRot.SetRotation(CVector3::AxisY, CMath::PI * GameTime().GetFrameDeltaTime());
	m_rotation *= qAddRot;
	m_skinModelRender->SetRotation(m_rotation);

	//��������
	auto diff = m_player->GetPosition() - m_position;
	if (diff.Length() < 100.0f) {
		m_game->NotifyGetStar();
		//�����擾��������炷�B
		auto ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/coinGet.wav");
		ss->Play(false);
		DeleteGO(this);
	}
}
