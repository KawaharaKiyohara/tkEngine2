#include "stdafx.h"
#include "StarRenderer.h"


StarRenderer::StarRenderer()
{
}


StarRenderer::~StarRenderer()
{
	DeleteGO(m_modelRender);
}
/*!
*@brief	�J�n���ɌĂ΂�鏈���B
*/
bool StarRenderer::Start()
{
	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/star.cmo", nullptr, 0, enFbxUpAxisZ, m_numStar);
	m_modelRender->SetShadowCasterFlag(true);
	m_modelRender->FindMaterial([&](CModelEffect* material) {
		//�}�e���A���h�c��ݒ肷��B
		material->SetMaterialID(enMaterialID_Star);
	});
	m_modelRender->SetEmissionColor({6.5f, 6.5f, 0.5f });

	return true;
}


void StarRenderer::UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
{
	m_modelRender->UpdateInstancingData(trans, rot, scale);
}