#pragma once

class Game;

class ScoreHUD final : public IGameObject
{
public:
	ScoreHUD();
	~ScoreHUD();
	bool Start() override;
	void Update() override;
private:
	prefab::CFontRender* m_fontRender = nullptr;	//�t�H���g�����_���[�B
	Game* m_game = nullptr;							//�Q�[���B
	float m_timer = 0.0f;
};

