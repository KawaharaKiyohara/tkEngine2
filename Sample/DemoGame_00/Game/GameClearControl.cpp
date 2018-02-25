#include "stdafx.h"
#include "GameClearControl.h"
#include "Player.h"
#include "GameCamera.h"
#include "GameClearCamera.h"
#include "Game.h"
#include "Fade.h"

GameClearControl::GameClearControl()
{
}


GameClearControl::~GameClearControl()
{
}
void GameClearControl::Awake()
{
	//�v���C���[�ɃN���A��ʒm�B
	FindGO<Player>("Player")->NotifyGameClear();
	FindGO<GameCamera>("GameCamera")->NotifyGameClear();
}
bool GameClearControl::Start()
{
	//�Q�[���N���A�J�������쐬�B
	m_gameClearCamera = NewGO<GameClearCamera>(0, "GameClearCamera");
	m_game = FindGO<Game>("Game");
	m_statScorePos = m_game->GetScorePosition();
	m_startScoreScale = m_game->GetScoreFontScale();
	m_font.SetFont(m_game->GetFont());
	m_font.SetShadowParam(true, 2.0f, CVector4::Black);
	return true;
}
void GameClearControl::Update()
{
	if (!m_isWaitFade) {
		m_timer += GameTime().GetFrameDeltaTime();
		//�X�R�A���ړ�������B
		static const CVector2 endPos = { -235.0f, 280.0f };
		float t = pow(min(m_timer, 1.0f) / 1.0f, 2.0f);
		CVector2 scorePos;
		scorePos.x = CMath::Lerp(t, m_statScorePos.x, endPos.x);
		scorePos.y = CMath::Lerp(t, m_statScorePos.y, endPos.y);
		static const float endScale = 1.2f;
		float scoreFontScale = CMath::Lerp(t, m_startScoreScale, endScale);

		m_game->SetScorePosition(scorePos);
		m_game->SetScoreFontScale(scoreFontScale);
		if (m_timer > 3.0f) {
			//�Q�[���I���B
			m_isEnd = true;
		}
		if (m_isEnd &&
			Pad(0).IsPressAnyKey()) {
			m_isWaitFade = true;
			FindGO<Fade>("Fade")->StartFadeOut();
		}
	}
	else {
		if (!FindGO<Fade>("Fade")->IsFade()) {
			DeleteGO(m_game);
		}
	}
	
}
void GameClearControl::OnDestroy()
{
	DeleteGO(m_gameClearCamera);
}
void GameClearControl::PostRender(CRenderContext& rc)
{
	if (m_isEnd) {
		//press any key��\���B
		m_font.Begin(rc);
		m_font.Draw(L"PRESS ANY KEY", CVector2::Zero, CVector4::Yellow);
		m_font.End(rc);
	}
}