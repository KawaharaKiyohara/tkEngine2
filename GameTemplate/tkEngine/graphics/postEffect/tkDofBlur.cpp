/*!
 * @brief	��ʊE�[�x�p�̃u���[�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkBlur.h"
#include "tkEngine/graphics/tkPresetRenderState.h"

namespace tkEngine{

	CDofBlur::CDofBlur()
	{
	}
	CDofBlur::~CDofBlur()
	{
	}
	void CDofBlur::Init( CShaderResourceView& srcTexture, float blurIntensity )
	{
		m_blur.Init(srcTexture, blurIntensity);

		//�V�F�[�_�[�����[�h�B
		m_vsXBlurShader.Load("shader/dof/blur.fx", "VSXBlur", CShader::EnType::VS);
		m_vsYBlurShader.Load("shader/dof/blur.fx", "VSYBlur", CShader::EnType::VS);
		m_psBlurShader.Load("shader/dof/blur.fx", "PSBlur", CShader::EnType::PS);
	}
	void CDofBlur::Execute(CRenderContext& rc)
	{
		m_blur.Execute(rc, [&](CRenderContext& rc, CBlur::EnRenderStep enRenderStep) {
			if (enRenderStep == CBlur::enRenderStep_XBlur) {
				//X�u���[�B
				rc.VSSetShader(m_vsXBlurShader);
				rc.PSSetShader(m_psBlurShader);
			}
			else if (enRenderStep == CBlur::enRenderStep_YBlur) {
				//Y�u���[�B
				rc.VSSetShader(m_vsYBlurShader);
				rc.PSSetShader(m_psBlurShader);
			}
		});
	}
}