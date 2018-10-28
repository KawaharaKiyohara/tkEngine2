#pragma once

/// <summary>
/// �n�ʃN���X�B
/// </summary>
class Ground : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Ground();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Ground();
	/// <summary>
	/// �J�n�����B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[�B
	CPhysicsStaticObject m_phyStaticObject;			//�����ÓI�I�u�W�F�N�g�B
	CShaderResourceView m_specTexSRV;				//�X�y�L�����}�b�v�̃V�F�[�_�[���\�[�X�r���[�B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CVector3 m_scale = CVector3::One;				//�g�嗦�B
};

