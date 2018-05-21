
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/sound/tkSoundSource.h"

namespace {
	const CVector3 START_POS = { -1088.16589f, 67.87, -567.0f };
}
class CSoundEmitter : public IGameObject {
private:
	float m_timer = 0.0f;
	float m_emitTime = 0.0f;
	std::string m_filePath;
public:
	void Init(float emitTime, const char* filePath)
	{
		m_emitTime = emitTime;
		m_filePath = filePath;
	}
	void Update()
	{
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > m_emitTime) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init(m_filePath.c_str());
			s->Play(false);
			DeleteGO(this);
		}
	}
};
bool Player::Start()
{
	//���f���f�[�^�����[�h�B
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	m_normalMap.CreateFromDDSTextureFromFile(L"sprite/utc_nomal.dds");
	m_specMap.CreateFromDDSTextureFromFile(L"sprite/utc_spec.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		//�}�e���A���h�c��ݒ肷��B
		material->SetMaterialID(enMaterialID_Chara);
		//�@���}�b�v�ƃX�y�L�����}�b�v��ݒ�B
		material->SetNormalMap(m_normalMap.GetBody());
		material->SetSpecularMap(m_specMap.GetBody());
	});

	m_animClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"animData/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"animData/KneelDown.tka");
	m_animClip[enAnimationClip_Clear].Load(L"animData/Clear.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_position = START_POS;
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animation.Init(m_skinModel, m_animClip, enAnimationClip_num);
	m_animation.Play(enAnimationClip_idle);
	m_charaLight = NewGO<prefab::CDirectionLight>(0);
	m_charaLight->SetDirection({ 1.0f, 0.0f, 0.0f });
	m_charaLight->SetLightingMaterialIDGroup(1 << enMaterialID_Chara);
	m_charaLight->SetColor({ 10.0f, 10.0f, 10.0f, 1.0f });
	m_charaCon.Init(20.0f, 68.0f, m_position);
	m_game = FindGO<Game>("Game");
	return true;
}
void Player::Turn()
{
	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (moveSpeedXZ.LengthSq() < 1.0f) {
		return;
	}
	m_rotation.SetRotation(CVector3::Up, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
}
void Player::UpdateFSM()
{
	
	static float JUMP_SPEED = 630.0f;
	switch (m_state) {
	case enState_Idle:
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		Move();
		if (Pad(0).IsTrigger(enButtonA)) {
			m_moveSpeed.y = JUMP_SPEED;
			m_state = enState_Jump;
		}else if (m_moveSpeed.LengthSq() > 0.001f) {
			//���͂�����B
			m_state = enState_Run;
		}
		break;
	case enState_Run:
		Move();
		
		if (m_moveSpeed.LengthSq() < 50.0f * 50.0f) {
			//���͂��Ȃ��Ȃ����B
			m_state = enState_Idle;
		}else if (Pad(0).IsTrigger(enButtonA)) {
			//���̎��_�ł�XZ�����̑��x���L�����Ă����B
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_state = enState_Jump;
		}
		break;
	case enState_Jump:
		Move();
		if (!m_charaCon.IsJump()) {
			if (m_moveSpeed.LengthSq() < 50.0f * 50.0f) {
				//���͂��Ȃ��Ȃ����B
				m_state = enState_Idle;
			}
			else {
				m_state = enState_Run;
			}
		}
		break;
	case enState_GameOver: {
		if (!m_animation.IsPlaying()) {
			m_game->NotifyRestart();
		}
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

	}break;
	case enState_WaitStartGameClear:
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > 0.5f) {
			
			CSoundEmitter* emitter = NewGO<CSoundEmitter>(0);
			emitter->Init(0.3f, "sound/uni1518.wav");
			m_state = enState_GameClear;
			m_timer = 0.0f;
		}
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		break;
	case enState_GameClear: {
		
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}break;
	}
}
void Player::Move()
{
	float MOVE_SPEED = 2400.0f;
	static float MOVE_SPEED_JUMP = 1000.0f;
	float x = Pad(0).GetLStickXF();
	float y = Pad(0).GetLStickYF();

	//�����x���v�Z�B
	CVector3 accForwardXZ = MainCamera().GetForward();
	CVector3 accRightXZ = MainCamera().GetRight();
	accForwardXZ.y = 0.0f;
	accForwardXZ.Normalize();
	accRightXZ.y = 0.0f;
	accRightXZ.Normalize();
	if (m_state == enState_Jump) {
		//�W�����v���ł��ɂ������]���ł���悤�ɂ���B
		accForwardXZ *= y * MOVE_SPEED_JUMP * GameTime().GetFrameDeltaTime();
		accRightXZ *= x * MOVE_SPEED_JUMP * GameTime().GetFrameDeltaTime();
	}
	else {
		accForwardXZ *= y * MOVE_SPEED * GameTime().GetFrameDeltaTime();
		accRightXZ *= x * MOVE_SPEED * GameTime().GetFrameDeltaTime();
	}

	//���C�́B
	CVector3 friction = m_moveSpeed;
	if (m_state == enState_Jump) {
		//�W�����v���̖��C�́B
		friction *= -1.0f;
	}
	else {
		friction *= -3.0f;
	}
	
	m_moveSpeed.x += friction.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z += friction.z * GameTime().GetFrameDeltaTime();
	//�����x��������B
	m_moveSpeed += accForwardXZ;
	m_moveSpeed += accRightXZ;
	m_moveSpeed.y += -1800.0f * GameTime().GetFrameDeltaTime();
	if (m_state == enState_Jump) {
		//�ړ����x�ɐ�����������B
		//�W�����v���ɃW�����v�O��葁���Ȃ邱�Ƃ͂Ȃ��B
		CVector3 moveSpeedXZ = { m_moveSpeed.x, 0.0f, m_moveSpeed.z };

		if (moveSpeedXZ.LengthSq() > m_moveSpeedWhenStartJump * m_moveSpeedWhenStartJump) {
			moveSpeedXZ.Normalize();
			moveSpeedXZ *= m_moveSpeedWhenStartJump;
			m_moveSpeed.x = moveSpeedXZ.x;
			m_moveSpeed.z = moveSpeedXZ.z;
		}
	}
}
void Player::AnimationController()
{
	if (m_state == enState_Jump) {
		m_animation.Play(enAnimationClip_jump, 0.2f);
	}
	else if( m_state == enState_Run
		|| m_state == enState_Idle
	){
		if (m_moveSpeed.LengthSq() > 600.0f * 600.0f) {
			//���胂�[�V�����B
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (m_moveSpeed.LengthSq() > 50.0f * 50.0f) {
			//���胂�[�V�����B
			m_animation.Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//�ҋ@���[�V����
			m_animation.Play(enAnimationClip_idle, 0.2f);
		}
	}
	else if (m_state == enState_GameClear) {
		m_animation.Play(enAnimationClip_Clear);
	}
	else if (m_state == enState_GameOver) {
		m_animation.Play(enAnimationClip_KneelDown);
	}
}
void Player::Update()
{
	AnimationController();

	Turn();
	
	if (m_position.y < -1000.0f && !m_game->IsGameOver()) {
		//�����ʒu�ɖ߂�B
		Game* game = FindGO<Game>("Game");
		game->NotifyGameOver();
	}

	UpdateFSM();
	//�L�����N�^���ړ�������B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	
	//�L�������C�g�̓J�����̕����ɂ���B
	m_charaLight->SetDirection(MainCamera().GetForward());
	CQuaternion qRot = CQuaternion::Identity;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);	//�Q�Ă�̂ŋN�����B
													//���[���h�s����X�V�B
	CQuaternion q ;
	q.Multiply(qRot, m_rotation);
	m_skinModel.Update(m_position, q, CVector3::One);

	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
}

void Player::NotifyGameOver()
{
	CSoundEmitter* emitter = NewGO<CSoundEmitter>(0);
	emitter->Init(0.6f, "sound/uni1482.wav");
	m_state = enState_GameOver;
}

void Player::NotifyGameClear()
{
	m_state = enState_WaitStartGameClear;
}
void Player::NotifyRestart()
{
	m_animation.Play(enAnimationClip_idle);
	m_state = enState_Idle;
	m_position = START_POS;
	m_charaCon.SetPosition(m_position);
	m_moveSpeed = CVector3::Zero;
}
void Player::OnDestroy()
{
	DeleteGO(m_charaLight);
}

void Player::Render(CRenderContext& rc)
{
	//�`��B
	m_skinModel.Draw(
		rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix()
	);

}