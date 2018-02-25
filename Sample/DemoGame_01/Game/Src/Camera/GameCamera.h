/*!
 * @brief	�Q�[���J�����B
 */
 
#pragma once

#include "tkEngine/camera/tkSpringCamera.h"

class CPlayer;

/*!
 * @brief	�Q�[���J�����B
 */
class CGameCamera : public IGameObject{
public:
	bool Start() override final;
	void Update() override final;
	/*!
	 *@brief	���_���擾�B
	 */
	CVector3 GetPosition() const
	{
		return m_springCamera.GetPosition();
	}
	/*!
	 *@brief	�����_���擾�B
	 */
	CVector3 GetTarget() const
	{
		return m_springCamera.GetTarget();
	}
private:
	
	
private:
	CSpringCamera m_springCamera;				//!<�o�l�J�����B
	CPlayer* m_player = nullptr;				//!<�v���C���B
	float m_toCameraPosDist;					//!<�����_���王�_�܂ł̋����B
};