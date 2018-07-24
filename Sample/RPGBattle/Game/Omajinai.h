#pragma once


#undef Attack
#undef Hoimi
#undef Zaoriku
#undef Baikiruto
#undef Sukuruto
#undef TenshiNoInori

/*!
*@	�U������B
*@details
* �����_���Ƀ����X�^�[���U�����܂��B
*/
#define Attack()	CommandAttackEnemy(m_commandsTmp, this)
	
/*!
*@brief	�z�C�~(�񕜎���)��������B
*@param	target	���@��������ΏہB
*/
#define Hoimi(target)	CommandHoim(m_commandsTmp, this, &target)
	
/*!
*@brief		�U�I���N(�h������)��������B
*
*@param		target		���@��������Ώ�
*/
#define Zaoriku(target)	CommandZaoriku(m_commandsTmp, this, &target)
/*!
*@brief	�o�C�L���g(�U���̓A�b�v����)��������B
*@details
*�^�[�Q�b�g�̍U���͂��啝�ɃA�b�v����B
*@param		target		���@��������Ώ�
*/
#define Baikiruto(target)	CommandBaikiruto(m_commandsTmp, this, &target)
/*!
*@brief	�X�N���g(�h��̓A�b�v����)��������B
*@details
*�p�[�e�B�S�̖̂h��͂��啝�ɃA�b�v����B
*/
#define Sukuruto()	CommandSukuruto(m_commandsTmp, this)
/*!
*@brief	�V�g�̋F���������B
*@details
* �������m���g�ɂ��������邱�Ƃ��Ȃ��A����ȋF��B
* ��x�������S���Ă������I�ɑh������A�������m�̉��`�B
*@param	target	���@��������Ώ�
*/
#define TenshiNoInori()	CommandTenshiNoInori(m_commandsTmp, this)