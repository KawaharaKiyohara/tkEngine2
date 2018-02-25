/*!
 * @brief	�w�i
 */

#include "stdafx.h"
#include "BackGround/BackGround.h"

/*!
 * @brief	�R���X�g���N�^�B
 */
CBackGround::CBackGround()
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
CBackGround::~CBackGround()
{
}

bool CBackGround::Start()
{
	m_skinModelData.Load(L"modelData/background.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(false);
	m_skinModel.SetShadowReceiverFlag(true);

	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateMeshObject(m_skinModel, CVector3::Zero, CQuaternion::Identity);
	return true;
}

void CBackGround::Update()
{
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}

void CBackGround::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
