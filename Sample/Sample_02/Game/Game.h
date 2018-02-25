#pragma once
class Game : public IGameObject
{
public:
	//�����o�֐��B
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	//�����o�ϐ��B
	CSkinModel m_skinModel;			//�X�L�����f���B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B

};

