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
	prefab::CSkinModelRender* m_unityChanModelRender = nullptr;
	prefab::CSkinModelRender* m_bgModelRender = nullptr;
	prefab::CSkinModelRender* m_starModelRender = nullptr;
	prefab::CDirectionLight* m_directionLight = nullptr;

	CVector3 m_unityChanPosition = cv3Zero;
};

