#include "stdafx.h"
#include "NPC.h"


NPC::NPC()
{
}


NPC::~NPC()
{
}
bool NPC::Start()
{
	//�ÎE�� A���擾�B
	m_actor = FindGO<GameActor>("�ÎE��");
	//�A�N�^�[�ɃR�}���h��ς�ł����B
	for (int i = 0; i < 180; i++) {		//180�t���[������B
		m_actor->AddCommand(&m_commandRun);
	}
	for (int i = 0; i < 20; i++) {		//���ɐ���B
		m_actor->AddCommand(&m_commandTurnLeft);
	}
	for (int i = 0; i < 60; i++) {		//60�t���[�������B
		m_actor->AddCommand(&m_commandWalk);
	}
	for (int i = 0; i < 40; i++) {		//�E�ɐ���B
		m_actor->AddCommand(&m_commandTurnRight);
	}
	for (int i = 0; i < 30; i++) {		//30�t���[�������B
		m_actor->AddCommand(&m_commandWalk);
	}
	//���K�@�R�}���h��ǉ�����NPC�𓮂����Ă݂�B�B
	//�ҋ@�ŏI���B
	m_actor->AddCommand(&m_commandIdle);
	return true;
}