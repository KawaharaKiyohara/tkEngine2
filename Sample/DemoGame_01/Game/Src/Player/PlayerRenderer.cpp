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
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, nullptr, L"modelData/Thethief_H.cmo");
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);

	//�@���}�b�v�ƃX�y�L�����}�b�v�����[�h�B
	m_normalMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_N.dds");
	m_specMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_S.dds");
	m_wnormalMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_N.dds");
	m_wspecMap.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_S.dds");
	//�@���}�b�v�ƃX�y�L�����}�b�v�����f���ɓ\��B
	m_skinModelRender->FindMaterial([&](CModelEffect* material)
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
	qRot.SetRotation(CVector3::AxisX, CMath::PI);
	qRot.Multiply(m_player->GetRotation(), qRot);
	m_skinModelRender->SetPosition(m_player->GetPosition());
	m_skinModelRender->SetRotation(qRot);

}
