#pragma once
#include "GameActor.h"
#include "Command.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
private:
	GameActor* m_gameActor = nullptr;
	typedef std::shared_ptr<ICommand> ICommandPtr;
	std::vector<ICommandPtr> m_commands;	//�R�}���h�̃��X�g�B
	int m_currentCommandPos = -1;			//���݂̃R�}���h�ʒu�B
	
};

