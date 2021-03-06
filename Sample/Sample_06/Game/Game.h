#pragma once
class Game : public IGameObject
{
public:
	/////////////////////////////////////////////
	//メンバ関数。
	/////////////////////////////////////////////
	Game();
	~Game();
	bool Start();
	void Update();
	
	/////////////////////////////////////////////
	//メンバ変数とか。
	/////////////////////////////////////////////
	prefab::CSpriteRender* m_spriteRender;
	CVector3	m_position;		//座標。
	CQuaternion m_rotation;	//回転。
	CVector3	m_scale = CVector3::One;	//拡大率。
};

