#pragma once
/// <summary>
/// �Q�[���N���A���o�B
/// </summary>
class GameClearEffect final : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameClearEffect();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameClearEffect();
	/// <summary>
	/// �J�n�B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �A�b�v�f�[�g�B
	/// </summary>
	void Update() override;
};

