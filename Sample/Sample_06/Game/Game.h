#pragma once
class Game : public IGameObject
{
public:
	/////////////////////////////////////////////
	//�����o�֐��B
	/////////////////////////////////////////////
	Game();
	~Game();
	bool Start();
	void Update();
	/*!
	*@brief	Render�֐������s���ꂽ��ŌĂ΂��`�揈��
	*@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	* 2D��Ԃŕ`�悵�����ꍇ��Render�֐��ł͂Ȃ�PostRender�ŕ`����s���悤�ɁB
	*/
	void PostRender(CRenderContext& rc);
	/////////////////////////////////////////////
	//�����o�ϐ��Ƃ��B
	/////////////////////////////////////////////
	CSprite m_sprite;				//�X�v���C�g�B
	CShaderResourceView m_texture;	//�e�N�X�`���B
	CVector3	m_position = CVector3::Zero;		//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
};

