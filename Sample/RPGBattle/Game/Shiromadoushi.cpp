#include "stdafx.h"
#include "Shiromadoushi.h"
#include "IAICommand.h"
#include "Game.h"

Shiromadoushi::Shiromadoushi()
{
}
Shiromadoushi::~Shiromadoushi()
{
}
//�������m��AI�͂����ɏ����B
void Shiromadoushi::GenerateAICommandList(std::deque<IAICommandUPtr>& commands)
{
	m_commandsTmp.clear();
	AI(*senshi, *ryu, *shiro);
	//�������m�ɋ�����Ă���s���͂P�^�[���R��܂ŁI
	for (int i = 0; i < 3 && i < m_commandsTmp.size(); i++) {
		commands.push_back(std::move(m_commandsTmp[i]));
	}
}