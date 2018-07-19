#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	LightManager().SetAmbientLight({ 5.0f, 5.0f, 5.0f });
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 100.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().SetPosition({ 0.0f, 100.0f, 200.0f });
	MainCamera().Update();

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_bgSkinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_bgSkinModelRender->Init(L"modelData/background.cmo");
	m_spec.CreateFromDDSTextureFromFile(L"sprite/test.dds");
	m_bgSkinModelRender->FindMaterial([&](CModelEffect* mat) {
		if (mat->EqualMaterialName(L"Ground") == true){
			mat->SetSpecularMap(m_spec.GetBody());
		}
	});
	return true;
}

void Game::Update()
{
	CVector3 toPos = MainCamera().GetPosition() - MainCamera().GetTarget();
	float x = -Pad(0).GetLStickXF();
	float z = -Pad(0).GetLStickYF();
	pos.x += x;
	pos.z += z;
	m_skinModelRender->SetPosition(pos);
	//�J�������X�V�B
	//�����_���v�Z����B
	CVector3 target = pos;
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 50.0f;

	CVector3 toCameraPosOld = toPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(toPos);
	//X������̉�]�B
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, toPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(toPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	CVector3 toPosDir = toPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J����������������B
		toPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����������������B
		toPos = toCameraPosOld;
	}

	//���_���v�Z����B
	CVector3 pos = target + toPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(pos);

	//�J�����̍X�V�B
	MainCamera().Update();
}