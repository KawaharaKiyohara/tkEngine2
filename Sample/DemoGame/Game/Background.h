/*!
 * @brief	�w�i�B
 */
#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class Background : public IGameObject{
public:
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy() override;
private:
	CSkinModel 		m_skinModel;		//!<�X�L�����f���B
	CSkinModelData	m_skinModelData;	//!<�X�L�����f���f�[�^�B
	CRigidBody		m_rigidBody;		//!<���́B
	CMeshCollider	m_meshCollider;		//!<���b�V���R���C�_�[�B
	ID3D11RasterizerState* m_rasterizerState = nullptr;	//!<���X�^���C�U�X�e�[�g�B
};