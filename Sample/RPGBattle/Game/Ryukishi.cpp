#include "stdafx.h"
#include "Ryukishi.h"
#include "IAICommand.h"

Ryukishi::Ryukishi()
{
}
Ryukishi::~Ryukishi()
{
}
void Ryukishi::GenerateAICommandList(std::deque<IAICommandUPtr>& commands)
{
	//�K���ɓG������B
	CommandAttackEnemy(commands, this);
}