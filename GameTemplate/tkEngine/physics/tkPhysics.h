#pragma once

#include "tkEngine/Physics/tkCollisionAttr.h"

namespace tkEngine{
	class CRigidBody;
	class CCharacterController;

	class CPhysicsWorld
	{
		btDefaultCollisionConfiguration*		collisionConfig = nullptr;
		btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<�Փˉ��������B
		btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
		btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
		btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<���[���h�B
	public:
		CPhysicsWorld();
		~CPhysicsWorld();
		void Init();
		void Update();
		void Release();
		/*!
		* @brief	�_�C�i�~�b�N���[���h���擾�B
		*/
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return dynamicWorld;
		}
		/*!
		* @brief	���̂�o�^�B
		*/
		void AddRigidBody(CRigidBody& rb);
		/*!
		* @brief	���̂�j���B
		*/
		void RemoveRigidBody(CRigidBody& rb);
		/*!
		* @brief	�R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
		*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
		*/
		void AddCollisionObject(btCollisionObject& colliObj)
		{
			dynamicWorld->addCollisionObject(&colliObj);
		}
		/*!
		* @brief	�R���W�����I�u�W�F�N�g�����[���h����폜�B
		*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
		*/
		void RemoveCollisionObject(btCollisionObject& colliObj)
		{
			dynamicWorld->removeCollisionObject(&colliObj);
		}
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}
		void ContactTest(
			btCollisionObject* colObj,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		void ContactTest(
			CRigidBody& rb,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		
		void ContactTest(
			CCharacterController& charaCon,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		

	};
}
