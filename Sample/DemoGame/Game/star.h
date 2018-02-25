#pragma once
class Player;
class StarRenderer;

class Star : public IGameObject
{
public:
	Star();
	~Star();
	bool Start() override;
	void Update() override;
	/*!
	 *@brief	�������B
	 */
	void Init(StarRenderer& starRenderer)
	{
		m_renderer = &starRenderer;
	}
	/*!
	 *@brief	���W��ݒ�B
	 */
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	 *@brief	���W���擾�B
	 */
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	StarRenderer*	m_renderer = nullptr;					//!<�����_���[�B
	CVector3		m_position = CVector3::Zero;			//!<���W�B
	CQuaternion		m_rotation = CQuaternion::Identity;
	static prefab::CDirectionLight* m_starLight;
	Player*			m_player = nullptr;
	bool			m_isGet = false;
	float			m_jumpSpeed = 0.0f;
	float			m_jumStartPosY = 0.0f;
};

