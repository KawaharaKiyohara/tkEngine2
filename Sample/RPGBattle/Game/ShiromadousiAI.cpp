#include "stdafx.h"
#include "Shiromadoushi.h"
#include "IAICommand.h"
#include "Game.h"

/////////////////////////////////////////////////
// �������m���g����R�}���h�ꗗ
/////////////////////////////////////////////////
/*!
*@	�U������B
*@details
* �����_���Ƀ����X�^�[���U�����܂��B
*/
#define Attack()
/*!
*@brief	�z�C�~(�񕜎���)��������B
*@param	target	���@��������ΏہB
*/
#define Hoimi(target)
/*!
*@brief		�U�I���N(�h������)��������B
*
*@param		target		���@��������Ώ�
*/
#define Zaoriku(target)
/*!
*@brief	�o�C�L���g(�U���̓A�b�v����)��������B
*@details
*�^�[�Q�b�g�̍U���͂��啝�ɃA�b�v����B
*@param		target		���@��������Ώ�
*/
#define Baikiruto(target)
/*!
*@brief	�X�N���g(�h��̓A�b�v����)��������B
*@details
*�p�[�e�B�S�̖̂h��͂��啝�ɃA�b�v����B
*/
#define Sukuruto()
/*!
*@brief	�V�g�̋F���������B
*@details
* �������m���g�ɂ��������邱�Ƃ��Ȃ��A����ȋF��B
* ��x�������S���Ă������I�ɑh������A�������m�̉��`�B
*@param	target	���@��������Ώ�
*/
#define TenshiNoInori()

#include "Omajinai.h"

/*!
*@brief	�������m��AI
*@param		senshi		��m
*@param		ryu			���R�m
*@param		shiro		�������m�B
*/
void Shiromadoushi::AI(
	AIAvator& senshi, 
	AIAvator& ryu,
	AIAvator& shiro 
)
{
	/////////////////////////////////////////////////
	// ��������`
	/////////////////////////////////////////////////
	
	/////////////////////////////////////////////////
	// �`�����܂ł̊Ԃɔ������m��AI�������I
	/////////////////////////////////////////////////
}