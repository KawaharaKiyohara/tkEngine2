#pragma once
class Game : public IGameObject
{
public:
	//////////////////////////////////////
	// �����o�֐��B
	//////////////////////////////////////
	Game();
	~Game();
	bool Start();
	void Update();
	//////////////////////////////////////
	// �����o�ϐ��B
	//////////////////////////////////////
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CQuaternion m_rotation = CQuaternion::Identity;
	int m_rotateMode = 0;	//0�͎�����]�A1�̓X�e�B�b�N�ŉ�]�B
};

