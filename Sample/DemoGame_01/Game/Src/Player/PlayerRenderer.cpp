/*!
 * @brief	�v���C���[�����_���[
 *@details
 * �v���C���[�̕`��֌W�̏������s���N���X�ł��B
 */

#include "stdafx.h"
#include "Player/Player.h"
#include "Player/PlayerRenderer.h"


void CPlayerRenderer::Awake()
{
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);

	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);

	//�@���}�b�v�ƃX�y�L�����}�b�v�����[�h�B
	m_normalMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_N.dds");
	m_specMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_S.dds");
	m_wnormalMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_N.dds");
	m_wspecMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_S.dds");
	//�@���}�b�v�ƃX�y�L�����}�b�v�����f���ɓ\��B
	m_skinModel.FindMaterial([&](CModelEffect* material)
	{
		if (material->EqualMaterialName(L"bodyMat")) {
			//�̂̃}�e���A���B
			material->SetNormalMap(m_normalMap.GetBody());
			material->SetSpecularMap(m_specMap.GetBody());
		}else if (material->EqualMaterialName(L"weapon")) {
			//����̃}�e���A���B
			material->SetNormalMap(m_wnormalMap.GetBody());
			material->SetSpecularMap(m_wspecMap.GetBody());
		}
	});
}

void CPlayerRenderer::Update()
{
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisX, CMath::PI * 0.5f);
	qRot.Multiply(m_player->GetRotation(), qRot);
	m_skinModel.Update(m_player->GetPosition(), qRot, CVector3::One, CSkinModel::enFbxUpAxisY);
}

void CPlayerRenderer::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc);
}