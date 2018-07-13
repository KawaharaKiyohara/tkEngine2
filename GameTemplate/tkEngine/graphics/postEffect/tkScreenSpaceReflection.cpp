/*!
 *@brief	Screen space reflection
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkScreenSpaceReflection.h"
#include "tkEngine/graphics/tkPresetRenderState.h"
#include "tkEngine/graphics/tkPresetSamplerState.h"

namespace tkEngine {
	void CScreenSpaceReflection::Release()
	{
	}
	void CScreenSpaceReflection::Init(const SGraphicsConfig& config)
	{
		m_isEnable = config.ssrConfig.isEnable;
		m_vsShader.Load("shader/ScreenSpaceReflection.fx", "VSMain", CShader::EnType::VS);
		m_psShader.Load("shader/ScreenSpaceReflection.fx", "PSMain", CShader::EnType::PS);
		m_cb.Create(nullptr, sizeof(SConstantBuffer));
	}
	/*!
	*@brief	�`��B
	*@param[in]		rc		�����_�����O�R���e�L�Xt�B
	*/
	void CScreenSpaceReflection::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		if (m_isEnable == false) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_ScreenSpaceReflection");
		rc.OMSetDepthStencilState(DepthStencilState::disable, 0);
		//���݂̃����_�����O�^�[�Q�b�g���擾�B
		CRenderTarget& rt = postEffect->GetFinalRenderTarget();
		//�����_�����O�^�[�Q�b�g��؂�ւ���B
		postEffect->ToggleFinalRenderTarget();
		CRenderTarget* renderTargets[] = {
			&postEffect->GetFinalRenderTarget()
		};
		//�萔�o�b�t�@���X�V���āA���W�X�^�ɐݒ�B
		SConstantBuffer cb;
		cb.cameraPos = MainCamera().GetPosition();
		cb.mViewProj = MainCamera().GetViewProjectionMatrix();
		cb.mViewProjInv.Inverse(MainCamera().GetViewProjectionMatrix());
		rc.UpdateSubresource(m_cb, &cb);
		rc.PSSetConstantBuffer(0, m_cb);

		CGBufferRender& gBuffer = GraphicsEngine().GetGBufferRender();
		rc.OMSetBlendState(AlphaBlendState::disable, 0, 0xFFFFFFFF);
		rc.PSSetSampler(0, *CPresetSamplerState::sampler_clamp_clamp_clamp_linear);
		rc.OMSetRenderTargets(1, renderTargets);
		rc.PSSetShaderResource(0, rt.GetRenderTargetSRV());
		rc.PSSetShaderResource(1, gBuffer.GetRenderTarget(enGBufferNormal).GetRenderTargetSRV());
		rc.PSSetShaderResource(2, gBuffer.GetRenderTarget(enGBufferDepth).GetRenderTargetSRV());
		rc.PSSetShaderResource(3, gBuffer.GetRenderTarget(enGBufferSpecular).GetRenderTargetSRV());

		rc.PSSetShader(m_psShader);
		rc.VSSetShader(m_vsShader);
		//���̓��C�A�E�g��ݒ�B
		rc.IASetInputLayout(m_vsShader.GetInputLayout());

		postEffect->DrawFullScreenQuad(rc);
		rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
		rc.PSUnsetShaderResource(0);
		EndGPUEvent();
	}
}

