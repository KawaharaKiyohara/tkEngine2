/*!
 *@brief	�}�b�v�`�b�v
 */

#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

namespace tkEngine{
	struct LevelObjectData;
	/*!
	 *@brief	�}�b�v�`�b�v�B
	 */
	class CMapChip : Noncopyable{
	public:
		CMapChip(LevelObjectData& objData);
		~CMapChip()
		{
			DeleteGO(m_modelRender);
		}
	private:
		prefab::CSkinModelRender* m_modelRender = nullptr;	//!<���f�������_���[�B
		CPhysicsStaticObject m_physicsStaticObject;			//!<�ÓI�����I�u�W�F�N�g�B
	};
}
