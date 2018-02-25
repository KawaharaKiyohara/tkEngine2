#pragma once

#include "ICommand.h"

///////////////////////////////////////////
/*!
 *@brief	�����R�}���h�B
 */
 ///////////////////////////////////////////
class Command_Walk : public ICommand
{
public:
	Command_Walk()
	{
	}
	~Command_Walk()
	{
	}

	/*!
	 *@brief	�R�}���h�����s�B
	 */
	void Execute(GameActor& actor) override;
};
///////////////////////////////////////////
/*!
*@brief	����R�}���h�B
*/
///////////////////////////////////////////
class Command_Run : public ICommand
{
public:
	Command_Run()
	{
	}
	~Command_Run()
	{
	}
	void Execute(GameActor& actor) override;
};
///////////////////////////////////////////
/*!
*@brief	�E�ɐ��񂷂�R�}���h�B
*/
///////////////////////////////////////////
class Command_TurnRight : public ICommand
{
public:
	Command_TurnRight()
	{
	}
	~Command_TurnRight()
	{
	}
	void Execute(GameActor& actor) override;
};
///////////////////////////////////////////
/*!
*@brief	���ɐ��񂷂�R�}���h�B
*/
///////////////////////////////////////////
class Command_TurnLeft : public ICommand
{
public:
	Command_TurnLeft()
	{
	}
	~Command_TurnLeft()
	{
	}
	void Execute(GameActor& actor) override;
};
///////////////////////////////////////////
/*!
*@brief	�ҋ@�R�}���h�B
*/
///////////////////////////////////////////
class Command_Idle : public ICommand
{
public:
	Command_Idle()
	{
	}
	~Command_Idle()
	{
	}
	void Execute(GameActor& actor) override;
};




