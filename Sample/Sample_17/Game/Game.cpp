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
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();
	
	//���f���f�[�^�����[�h�B
	skinModelData.Load(L"modelData/unityChan.cmo");
	skinModel.Init(skinModelData);
	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f });
	
	return true;
}
void Game::Update()
{
	if (Pad(0).IsTrigger(enButtonA)) {
		//�G�t�F�N�g���쐬�B
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		//�G�t�F�N�g���Đ��B
		effect->Play(L"effect/test.efk");
		CVector3 emitPos = m_pos;
		emitPos.y += 10.0f;
		effect->SetPosition(emitPos);
	}
	m_pos.z += Pad(0).GetLStickXF();
	m_pos.y += Pad(0).GetLStickYF();
	skinModel.Update(m_pos, CQuaternion::Identity, { 0.1f, 0.1f, 0.1f });
}
void Game::Render(CRenderContext& rc)
{
	skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}