/*!
 *@brief	�}�b�v�`�b�v�̃����_���[�B
 */

#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

namespace tkEngine{
	struct LevelObjectData;
	/*!
	 *@brief	�}�b�v�`�b�v�����_���[�B
	 */
	class CMapChipRender : Noncopyable{
	public:
		CMapChipRender();
		~CMapChipRender();
	private:
		prefab::CSkinModelRender* m_modelRender = nullptr;	//!<���f�������_���[�B
	};
}
