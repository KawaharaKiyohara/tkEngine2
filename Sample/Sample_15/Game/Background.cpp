#include "stdafx.h"
#include "Background.h"



void Background::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool Background::Start()
{
	//���f�������_���[���쐬�B
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/background.cmo");
	m_skinModelRender->SetShadowReceiverFlag(true);
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_physicsStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity);
	return true;
}

