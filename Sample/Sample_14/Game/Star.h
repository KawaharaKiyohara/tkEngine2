#pragma once
class Star : public IGameObject
{
public:
	Star();
	~Star();
	bool Start();
	void Update();
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One;
	prefab::CSkinModelRender* m_modelRender = nullptr;		//���f�������_���[�B
	float m_moveSpeed = 1.0f;		//Y�����̈ړ����x
};

