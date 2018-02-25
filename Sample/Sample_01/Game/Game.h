#pragma once
class Game : public IGameObject
{
public:
	//�����o�֐��B
	Game();
	~Game();
	bool Start();
	void Update();
	//�����o�ϐ��B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B

};

