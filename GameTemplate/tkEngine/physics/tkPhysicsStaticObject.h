/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

namespace tkEngine{
	/*!
	 * @brief	�ÓI�����I�u�W�F�N�g
	 */
	class CPhysicsStaticObject{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CPhysicsStaticObject();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CPhysicsStaticObject();
		/*!
		* @brief	�{�b�N�X�`��̐ÓI�����I�u�W�F�N�g���쐬�B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in]	size		�T�C�Y�B
		*/
		void CreateBox( CVector3 pos, CQuaternion rot, CVector3 size);
		/*!
		 * @brief	���b�V���̐ÓI�I�u�W�F�N�g���쐬�B
		 *@param[in]	skinModel	�X�L�����f���B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 *@param[in]	scale		�g�嗦�B
		 */
		void CreateMeshObject(CSkinModel& skinModel, CVector3 pos, CQuaternion rot, CVector3 scale);
		void CreateMeshObject(prefab::CSkinModelRender* skinModelRender, CVector3 pos, CQuaternion rot, CVector3 scale);
	private:
		/*!
		* @brief	����B
		*/
		void Release();
		/*!
		* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
		*/
		void CreateCommon(CVector3 pos, CQuaternion rot, std::unique_ptr<ICollider> collider);
	private:
	//	CMeshCollider m_meshCollider;		//!<���b�V���R���C�_�[�B
		CRigidBody m_rigidBody;				//!<���́B
		std::unique_ptr<ICollider> m_collider;	//!<�R���C�_�[�B
	};
}