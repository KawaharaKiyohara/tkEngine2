/*!
 * @brief	�w�i
 */

#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

class CBackGround : public IGameObject{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CBackGround();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~CBackGround();
	/*!
	 * @brief	�X�^�[�g�B
	 */
	bool Start() override;
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
};