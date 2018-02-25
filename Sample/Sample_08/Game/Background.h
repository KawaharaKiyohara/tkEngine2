#pragma once

//CMeshCollider��CRigidBody���g�p�������ꍇ�͉��L�̃w�b�_�[�t�@�C�����C���N���[�h����K�v������B
#include "tkEngine/physics/tkPhysicsStaticObject.h"

class Background : public IGameObject
{
public:
	bool Start() override;
	void OnDestroy() override;
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CPhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�B
	CVector3 m_position = CVector3::Zero;			//���W�B
};

