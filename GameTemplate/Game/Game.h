#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_uniSkinModelRender = nullptr;	//手前のスキンモデルレンダラー。
	prefab::CSkinModelRender* m_uniSkinModelRender2 = nullptr;	//手前のスキンモデルレンダラー。
	prefab::CSkinModelRender* m_bgSkinModelRender = nullptr;	//背景のスキンモデルレンダラー。
	prefab::CSky* m_sky = nullptr;	//空。
};

