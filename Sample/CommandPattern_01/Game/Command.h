#pragma once

#include "ICommand.h"

///////////////////////////////////////////
/*!
 *@brief	�O�ɕ����R�}���h�B
 */
 ///////////////////////////////////////////
class Command_WalkForward : public ICommand
{
public:
	Command_WalkForward()
	{
	}
	~Command_WalkForward()
	{
	}

	/*!
	 *@brief	�R�}���h�����s�B
	 */
	void Execute(GameActor& actor) override;
	/*!
	*@brief		�A���h�D�����s�B
	*/
	void Undo(GameActor& actor) override;
private:
	CVector3 m_beforePos = CVector3::Zero;
};
///////////////////////////////////////////
/*!
*@brief	���ɕ����R�}���h�B
*/
///////////////////////////////////////////
class Command_WalkBack : public ICommand
{
public:
	Command_WalkBack()
	{
	}
	~Command_WalkBack()
	{
	}
	void Execute(GameActor& actor) override;
	/*!
	*@brief		�A���h�D�����s�B
	*/
	void Undo(GameActor& actor) override;
private:
	CVector3 m_beforePos = CVector3::Zero;
};
///////////////////////////////////////////
/*!
*@brief	�E�ɕ����R�}���h�B
*/
///////////////////////////////////////////
class Command_WalkRight : public ICommand
{
public:
	Command_WalkRight()
	{
	}
	~Command_WalkRight()
	{
	}
	void Execute(GameActor& actor) override;
	/*!
	*@brief		�A���h�D�����s�B
	*/
	void Undo(GameActor& actor) override;
private:
	CVector3 m_beforePos = CVector3::Zero;
};
///////////////////////////////////////////
/*!
*@brief	���ɕ����R�}���h�B
*/
///////////////////////////////////////////
class Command_WalkLeft : public ICommand
{
public:
	Command_WalkLeft()
	{
	}
	~Command_WalkLeft()
	{
	}
	void Execute(GameActor& actor) override;
	/*!
	*@brief		�A���h�D�����s�B
	*/
	void Undo(GameActor& actor) override;
private:
	CVector3 m_beforePos = CVector3::Zero;
};

class Command_WalkForwardRight : public ICommand {
public:
	Command_WalkForwardRight()
	{
	}
	~Command_WalkForwardRight()
	{
	}
	void Execute(GameActor& actor) override;
	/*!
	*@brief		�A���h�D�����s�B
	*/
	void Undo(GameActor& actor) override;
private:
	CVector3 m_beforePos = CVector3::Zero;
};