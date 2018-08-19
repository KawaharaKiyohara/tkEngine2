#include "stdafx.h"
#include "Star.h"


Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/star/star.cmo");
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
}
void Star::Update()
{
	//Star�ɍ��W��`����B
	m_skinModelRender->SetPosition(m_position);
	//���t���[��Y������ɏ����Â񂷁B
	CQuaternion qAddRot;
	qAddRot.SetRotationDeg(CVector3::AxisY, 2.0f);
	//�N�H�[�^�j�I���̏�Z�͉�]�̉��Z�Ɠ����B
	//���̉�]�N�H�[�^�j�I���ɖ��t���[��Y������ɂQ�x�̉�]�����Z���Ă����B
	m_rotation *= qAddRot;
	m_skinModelRender->SetRotation(m_rotation);
}