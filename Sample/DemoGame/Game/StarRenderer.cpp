#include "stdafx.h"
#include "StarRenderer.h"


StarRenderer::StarRenderer()
{
}


StarRenderer::~StarRenderer()
{
}
/*!
*@brief	�J�n���ɌĂ΂�鏈���B
*/
bool StarRenderer::Start()
{
	m_skinModelData.Load(L"modelData/star.cmo");
	m_skinModel.Init(m_skinModelData, m_numStar);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		//�}�e���A���h�c��ݒ肷��B
		material->SetMaterialID(enMaterialID_Star);
	});

	return true;
}

void StarRenderer::PreUpdate() 
{
	m_skinModel.BeginUpdateInstancingData();
}

void StarRenderer::PostUpdate()
{
	m_skinModel.EndUpdateInstancingData();
}
void StarRenderer::UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
{
	m_skinModel.UpdateInstancingData(trans, rot, scale);	
}
/*!
*@brief	�`��
*/
void StarRenderer::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(
		renderContext, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix()
	);
}