#pragma once
class Game : public IGameObject
{
public:
	//�����o�֐��B
	
	void OnDestroy() override final;
	bool Start() override final;
	void Update() override final;
	
	//�����o�ϐ��B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B

};

