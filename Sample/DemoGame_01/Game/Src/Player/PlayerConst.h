/*!
 * @brief	�v���C���[�֌W�̒萔�B
 */


#pragma once


class CPlayerConst{
public:
	static const float RUN_SPEED;		//�v���C���[�̈ړ����x�B
	/*!
	 * @brief	�v���C���[�̏�ԁB
	 */
	enum EnState {
		enState_Idle,		//!<�ҋ@�X�e�[�g�B
		enState_Walk,		//!<�����X�e�[�g�B
		enState_Run,		//!<����X�e�[�g�B
		enState_Jump,		//!<�W�����v�X�e�[�g�B
		enState_Invalid,	//!<�����X�e�[�g�B
	};
};