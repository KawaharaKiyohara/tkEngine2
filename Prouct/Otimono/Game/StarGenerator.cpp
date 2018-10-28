#include "stdafx.h"
#include "StarGenerator.h"
#include "Star.h"
#include "GameObjectName.h"
StarGenerator::StarGenerator()
{
}


StarGenerator::~StarGenerator()
{
}

void StarGenerator::Update()
{
	//�������̃C���^�[�o���^�C���B(�P�ʁF�b)
	const float STAR_GENERATE_INTERVAL = 2.0f;
	m_timer += GameTime().GetFrameDeltaTime();

	if (m_timer > STAR_GENERATE_INTERVAL) {
		//��莞�Ԃ������̂Ő��𐶐�����B
		NewGO<Star>(0, STAR_NAME);
		m_timer = 0.0f;
	}
}
