#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}
bool Player::Start()
{
	//�A�N�^�[�������B
	m_gameActor = FindGO<GameActor>("�ÎE��");
	return true;
}
void Player::Update()
{
	ICommandPtr command;
	//�O�i[XBox�R���g���[���@: Y�A�L�[�{�[�h : I ]
	//���[XBox�R���g���[���@: B�A�L�[�{�[�h : K ]
	//�E  [XBox�R���g���[���@: X�A�L�[�{�[�h : L ]
	//��  [XBox�R���g���[���@: A�A�L�[�{�[�h : J ]
	
	//Question 1 Command.h,cpp�ɉE�΂ߑO�Ɉړ�����R�}���h��ǉ����āA�ړ��ł���悤�ɂ��Ȃ����B
	//			 �E�΂ߑO�͑O�i�{�E�̃L�[���͂ōs���Ȃ����B
	//Question 2 Command.h,cpp�ɍ��΂ߑO�Ɉړ�����R�}���h��ǉ����āA�ړ��ł���悤�ɂ��Ȃ����B
	//			 ���΂ߑO�͑O�i�{���̃L�[���͂ōs���Ȃ����B
	if (Pad(0).IsPress(enButtonY)
		&& Pad(0).IsPress(enButtonX)) {
		command = std::make_shared<Command_WalkForwardRight>();
	}else if (Pad(0).IsPress(enButtonY)) {
		//�O�ɐi�ރR�}���h�𐶐��B
		command =std::make_shared<Command_WalkForward>();
	}else if (Pad(0).IsPress(enButtonB)) {
		//���ɐi�ރR�}���h�𐶐��B
		command = std::make_shared<Command_WalkBack>();
	}
	else if (Pad(0).IsPress(enButtonX)) {
		//�E�ɐi�ރR�}���h�𐶐��B
		command = std::make_shared<Command_WalkRight>();
	}
	else if (Pad(0).IsPress(enButtonA)) {
		//���ɐi�ރR�}���h�𐶐��B
		command = std::make_shared<Command_WalkLeft>();
	}
	
	if (command != nullptr) {
		//�R�}���h����������Ă���B
		if (m_currentCommandPos != m_commands.size() - 1) {
			//���݂̃R�}���h�ʒu�����͍폜����B
			m_commands.resize(m_currentCommandPos + 1);
		}
		command->Execute(*m_gameActor);
		//�R�}���h�̗����ɐςށB
		m_commands.push_back(command);
		m_currentCommandPos++;
	}
	//�A���h�D
	if (GetAsyncKeyState('Z') 
		&& GetAsyncKeyState(VK_CONTROL) 
		&& m_currentCommandPos >= 0
	) {
		//�A���h�D���s���B
		m_commands[m_currentCommandPos]->Undo(*m_gameActor);
		m_currentCommandPos--;
	}
	
	//���h�D
	if (GetAsyncKeyState('Y')
		&& GetAsyncKeyState(VK_CONTROL)
		&& m_currentCommandPos + 1 < m_commands.size()
		) {
		
		//���h�D���s���B
		m_currentCommandPos++;
		m_commands[m_currentCommandPos]->Execute(*m_gameActor);
	}
	
}