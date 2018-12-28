/*!
 * @brief	�w�i�B
 */
#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class Background : public IGameObject{
public:
	bool Start();	
	void OnDestroy() override;
private:
	prefab::CSkinModelRender* m_modelRender = nullptr;	//!<���f�������_���B
	CShaderResourceView m_specMap;		//�X�y�L�����}�b�v�B
	CRigidBody		m_rigidBody;		//!<���́B
	CMeshCollider	m_meshCollider;		//!<���b�V���R���C�_�[�B
	ID3D11RasterizerState* m_rasterizerState = nullptr;	//!<���X�^���C�U�X�e�[�g�B
};