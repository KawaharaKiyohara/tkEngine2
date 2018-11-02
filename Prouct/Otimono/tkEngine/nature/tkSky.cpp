#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/nature/tkSky.h"

namespace tkEngine {
	namespace prefab {
		CSky::CSky()
		{
		}


		CSky::~CSky()
		{
			DeleteGO(m_skinModelRender);
		}

		bool CSky::Start()
		{
			m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender->Init(L"modelData/sky.cmo");
			//��͓���ȃ����_�����O���s���̂ŁAForward�����_�����O�̕`��p�X�ŕ`�悷��B
			m_skinModelRender->SetForwardRenderFlag(true);
			m_skyCube.CreateFromDDSTextureFromFile(L"modelData/preset/skyCubeMap.dds");
			//�Q�ƃJ�E���^���グ�Ă����Ȃ��ƁA����ς݂̃e�N�X�`���ɃA�N�Z�X�����Ⴄ�B
			m_skyCube.AddRef();
			m_psSkyShader.Load("shader/model.fx", "PSMain_SkyCube", CShader::EnType::PS);
			//�}�e���A���ɃN�G���������āA�V�F�[�_�[�ƃe�N�X�`���������ւ��邺�B
			m_skinModelRender->FindMaterial([&](CModelEffect* mat) {
				mat->SetRender3DModelPSShader(m_psSkyShader);
				mat->SetDiffuseTexture(m_skyCube.GetBody());
			});
			return true;
		}
		void CSky::Update()
		{
			if (m_isDirty == true) {
				//�X�V�̕K�v����B
				m_skinModelRender->SetScale(m_scale);
				m_skinModelRender->SetEmissionColor(m_emissionColor);
				m_isDirty = false;
			}
		}
	}
}