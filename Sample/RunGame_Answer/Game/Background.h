#pragma once
class Background : public IGameObject
{
public:
	Background();
	~Background();
	
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;		//�ÓI�����I�u�W�F�N�g�B
};

