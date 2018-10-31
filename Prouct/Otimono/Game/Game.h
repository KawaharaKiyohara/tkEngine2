#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Game : public IGameObject
{
public:
	/// <summary>
	/// �Q�[���̃X�e�[�g�B
	/// </summary>
	enum EnState {
		enState_Playing,	//�v���C���B
		enState_Timeup,		//�^�C���A�b�v�B
	};
	Game();
	~Game();
	bool Start();
	void Update();
	/// <summary>
	/// �v���C���[���E�������̐����擾����B
	/// </summary>
	/// <returns></returns>
	int GetStarCount() const
	{
		return m_getStarCount;
	}
	/// <summary>
	/// ������������Ƃ�ʒm����B
	/// </summary>
	void NotifyGetStar()
	{
		m_getStarCount++;
	}
	/// <summary>
	/// �Q�[���̎c�莞�Ԃ��擾���擾�B
	/// </summary>
	/// <returns></returns>
	float GetRestTime() const
	{
		return m_restTimer;
	}
	/// <summary>
	/// �Q�[���̃v���C��Ԃ��擾�B
	/// </summary>
	/// <returns></returns>
	EnState GetState() const
	{
		return m_state;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CLevel m_level;
	int m_getStarCount = 0;										//�擾�������̐��B
	prefab::CSoundSource* m_bgm = nullptr;						//BGM
	float m_restTimer = 5.0f;									//�Q�[���̎c�莞�ԁB�P�ʁF�b�B
	EnState m_state = enState_Playing;							//�Q�[���̃X�e�[�g�B
	float m_clearEffectTimer = 0.0f;							//Clear���o�^�C���B
};

