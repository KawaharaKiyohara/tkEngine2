#pragma once
class Game : public IGameObject
{
public:
	/////////////////////////////////////////////
	//�����o�֐��B
	/////////////////////////////////////////////
	Game();
	~Game();
	bool Start();
	void Update();
	
	/////////////////////////////////////////////
	//�����o�ϐ��Ƃ��B
	/////////////////////////////////////////////
	prefab::CSpriteRender* m_spriteRender;
	CVector3	m_position;		//���W�B
	CQuaternion m_rotation;	//��]�B
	CVector3	m_scale = CVector3::One;	//�g�嗦�B
};

