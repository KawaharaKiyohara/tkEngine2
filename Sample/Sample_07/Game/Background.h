#pragma once

//CMeshCollider��CRigidBody���g�p�������ꍇ�͉��L�̃w�b�_�[�t�@�C�����C���N���[�h����K�v������B
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class Background : public IGameObject
{
public:
	Background();
	~Background();
	void Update();
	void Render(CRenderContext& rc);
	bool Start();
	void OnDestroy();
private:
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;			//�X�L�����f���B
	CVector3 m_position = CVector3::Zero;	//���W�B
	CMeshCollider m_meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody m_rigidBody;			//���́B
};

