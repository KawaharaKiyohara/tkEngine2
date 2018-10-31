#pragma once

class Game;

/// <summary>
/// �^�C�}�[HUD
/// </summary>
class TimerHUD final : public IGameObject{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	TimerHUD();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~TimerHUD();
	/// <summary>
	/// �����[����
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �����ՂŁ[��
	/// </summary>
	void Update() override;
private:
	prefab::CFontRender* m_fontRender = nullptr;	//�t�H���g�B
	Game* m_game = nullptr;
};

