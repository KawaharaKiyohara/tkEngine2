#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "BattleHud.h"
#include "IAICommand.h"

class AIAvator;

class Enemy;
enum EnMaterialID {
	enMaterialID_Enemy = 1 ,
};
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	BattleHud& GetBattleHUD()
	{
		return m_hud;
	}
	
private:
	enum EnStep {
		enStepWaitBattleStart,		//�o�g���J�n�҂��B
		enStepDecideCommand,		//AI�̃R�}���h�����蒆�B
		enStepExecuteCommand,		//AI�̃R�}���h�����s���B
		enStepGameOver,				//GameOver
		enStepGameClear,			//GameClear
	};
	CLevel level;
	BattleHud m_hud;
	
	std::vector<AIAvator*> m_aiAvatorList;
	std::vector<prefab::CDirectionLight*> m_dirLight;
	std::vector<prefab::CPointLight*> m_pointLight;
	EnStep m_step = enStepWaitBattleStart;	//���s�X�e�b�v�B
	std::deque<IAICommandUPtr> m_aiCommandList;
	prefab::CSoundSource* m_bgm = nullptr;	//BGM
	bool m_isPlayEnemyVoice = false;
	float m_timer = 0.0f;
	int m_currentAvatorNo = 0;
};

extern AIAvator* shiro;
extern AIAvator* ryu;
extern AIAvator* senshi;
extern AIAvator* enemy_00;
extern AIAvator* enemy_01;
extern AIAvator* enemy_02;
extern Game* g_game;

