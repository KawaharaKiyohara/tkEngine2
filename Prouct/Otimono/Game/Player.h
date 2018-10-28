#pragma once
/// <summary>
/// �v���C���[�N���X�B
/// </summary>
class Player : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Player();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �v���C���[�̃��[���h���W���擾�B
	/// </summary>
	/// <returns>�v���C���[�̃��[���h���W</returns>
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3::Zero;					//���W�B
	CCharacterController m_charaCon;						//�L�����R���B
	CVector3 m_moveSpeed = CVector3::Zero;					//�ړ����x�B(�P��:cm/sec)
};

