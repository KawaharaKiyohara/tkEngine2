#pragma once
class StarGenerator : public IGameObject
{
public:
	StarGenerator();
	~StarGenerator();
	void Update() override;
private:
	float m_timer = 0.0f;	//�^�C�}�[(�P��:�b)
};

