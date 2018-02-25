#include "stdafx.h"
#include "GameActor.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "ICommand.h"

GameActor::GameActor()
{
}


GameActor::~GameActor()
{
}
bool GameActor::Start()
{
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		50.0f,			//�����B
		-980.0f,		//�d�́A
		m_position		//�����ʒu�B
	);
	//�A�j���[�V�������������B
	InitAnimation();

	//�@���}�b�v�����[�h�B
	m_normalMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_N.dds");
	m_specularMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_S.dds");
	m_wnormalMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_N.dds");
	m_wspecularMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_S.dds");

	int materialID = 1;
	//�}�e���A��ID��ݒ�
	m_skinModel.FindMaterial([&](auto material) {
		material->SetMaterialID(materialID);
		if (material->EqualMaterialName(L"bodyMat")) {
			//�̂̃}�e���A���B
			material->SetNormalMap(m_normalMapSRV.GetBody());
			material->SetSpecularMap(m_specularMapSRV.GetBody());
		}
		else if (material->EqualMaterialName(L"weapon")) {
			//����B
			material->SetNormalMap(m_wnormalMapSRV.GetBody());
			material->SetSpecularMap(m_wspecularMapSRV.GetBody());
		}
	});
	//�L�������C�g�𐶐��B
	m_directionLig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̐F��ݒ�B
	m_directionLig->SetColor({ 10.5f, 10.5f, 10.5f, 1.0f });
	m_directionLig->SetLightingMaterialIDGroup(1 << materialID);
	return true;
}
void GameActor::InitAnimation()
{
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animationClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animationClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animationClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	//���[�v�t���O��ݒ肷��B
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	//�A�j���[�V�������������B
	m_animation.Init(m_skinModelData, m_animationClip, enAnimationClip_num);
	//�ҋ@�A�j���[�V�����𗬂��B
	PlayAnimation(enAnimationClip_idle);
	m_animation.Play(enAnimationClip_idle);
}

void GameActor::Walk()
{
	PlayAnimation(enAnimationClip_walk);
	CVector3 moveSpeed = m_moveDir * 80.0f;
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), moveSpeed);
}

void GameActor::Run()
{
	PlayAnimation(enAnimationClip_run);
	CVector3 moveSpeed = m_moveDir * 160.0f;
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), moveSpeed);
}

void GameActor::Idle()
{
	PlayAnimation(enAnimationClip_idle);
}

void GameActor::TurnLeft()
{
	PlayAnimation(enAnimationClip_walk);
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, -3.0f);
	qRot.Multiply(m_moveDir);
	m_moveDir.Normalize();
	
}

void GameActor::TurnRight()
{
	PlayAnimation(enAnimationClip_walk);
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 3.0f);
	qRot.Multiply(m_moveDir);
	m_moveDir.Normalize();
}
void GameActor::ExecuteCommand()
{
	if (m_commands.empty()) {
		return;
	}
	m_commands.front()->Execute(*this);
	m_commands.pop_front();
}
void GameActor::ExecuteRecord()
{
	if (m_commandsRecord.empty()) {
		//���R�[�h�̍Đ��I���B
		m_isPlayRecord = false;
		return;
	}
	m_commandsRecord.front()->Execute(*this);
	m_commandsRecord.pop_front();
}
void GameActor::Update()
{
	if (!m_isPlayRecord) {
		//�R�}���h�����s�B
		ExecuteCommand();
	}
	else {
		//���R�[�h�Đ��B
		ExecuteRecord();
	}
	//�A�j���[�V������i�߂�B
	m_animation.Update(GameTime().GetFrameDeltaTime());
	//�L�����ɂ͏��D���C�g�𓖂Ă�
	m_directionLig->SetDirection(MainCamera().GetForward());
	//���������B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeedDown);

	float angle = atan2(m_moveDir.x, m_moveDir.z);
	m_rotation.SetRotation(CVector3::AxisY, angle);
	//���[���h�s����X�V�B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳�p�̉�]�N�H�[�^�j�I�����v�Z�B
	//qRot��]�ƃL�����̉�]����Z���č�������B
	qRot.Multiply(m_rotation, qRot);
	m_skinModel.Update(m_position, qRot, CVector3::One);
}
void GameActor::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
