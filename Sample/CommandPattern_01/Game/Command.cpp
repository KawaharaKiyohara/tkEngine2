#include "stdafx.h"
#include "Command.h"


///////////////////////////////////////////
/*!
*@brief	�O�ɕ����R�}���h�B
*/
///////////////////////////////////////////
void Command_WalkForward::Execute(GameActor& actor)
{
	m_beforePos = actor.GetPosition();
	actor.Walk({0.0f, 0.0f, -200.0f});
}

void Command_WalkForward::Undo(GameActor& actor)
{
	actor.SetPosition(m_beforePos);
}
///////////////////////////////////////////
/*!
*@brief	���ɕ����R�}���h�B
*/
///////////////////////////////////////////
void Command_WalkBack::Execute(GameActor& actor)
{
	m_beforePos = actor.GetPosition();
	actor.Walk({ 0.0f, 0.0f, 200.0f });
}
void Command_WalkBack::Undo(GameActor& actor)
{
	actor.SetPosition(m_beforePos);
}
///////////////////////////////////////////
/*!
*@brief	�E�ɕ����R�}���h�B
*/
///////////////////////////////////////////
void Command_WalkRight::Execute(GameActor& actor)
{
	m_beforePos = actor.GetPosition();
	actor.Walk({ -200.0f, 0.0f, 0.0f });
}
void Command_WalkRight::Undo(GameActor& actor)
{
	actor.SetPosition(m_beforePos);
}
///////////////////////////////////////////
/*!
*@brief	���ɕ����R�}���h�B
*/
///////////////////////////////////////////
void Command_WalkLeft::Execute(GameActor& actor)
{
	m_beforePos = actor.GetPosition();
	actor.Walk({ 200.0f, 0.0f, 0.0f });
}
void Command_WalkLeft::Undo(GameActor& actor)
{
	actor.SetPosition(m_beforePos);
}

void Command_WalkForwardRight::Execute(GameActor& actor)
{
	m_beforePos = actor.GetPosition();
	actor.Walk({ -200.0f, 0.0f, -200.0f });
}
/*!
*@brief		�A���h�D�����s�B
*/
void Command_WalkForwardRight::Undo(GameActor& actor)
{
	actor.SetPosition(m_beforePos);
}