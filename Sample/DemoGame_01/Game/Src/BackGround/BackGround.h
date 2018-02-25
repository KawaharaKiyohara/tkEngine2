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
	/*!
	 * @brief	�X�V�B
	 */
	void Update() override;
	/*!
	 * @brief	�`��B
	 */
	void Render(CRenderContext& rc) override;
private:
	CSkinModel	m_skinModel;				//!<���f���B
	CSkinModelData m_skinModelData;			//!<���f���f�[�^�B
	CPhysicsStaticObject m_phyStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
};