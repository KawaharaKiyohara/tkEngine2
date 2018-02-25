#pragma once

#include "GameActor.h"


/*!
 *@brief	�R�}���h�̃C���^�[�t�F�[�X�N���X�B
 */
class ICommand
{
public:
	ICommand()
	{
	}
	virtual ~ICommand()
	{
	}
	/*!
	 *@brief	�R�}���h�����s�B
	 */
	virtual void Execute(GameActor& player) = 0;
};

