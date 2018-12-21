/// <summary>
/// DOF(��ʊE�[�x
/// </summary>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkDof.h"
#include "tkEngine/graphics/tkPresetRenderState.h"
#include "tkEngine/graphics/tkPresetSamplerState.h"

namespace tkEngine {
	CDof::CDof()
	{
	}
	CDof::~CDof()
	{
		Release();
	}
	void CDof::Release()
	{
		m_createDofMaskAndCalcCocParam.calcCocAndColorRt.Release();
		m_createDofMaskAndCalcCocParam.dofMaskRt.Release();
		m_createDofMaskAndCalcCocParam.vs.Release();
		m_createDofMaskAndCalcCocParam.ps.Release();
		m_createDofMaskAndCalcCocParam.samplerState.Release();
		m_createDofMaskAndCalcCocParam.cb.Release();
		if (m_createDofMaskAndCalcCocParam.blendState != nullptr) {
			m_createDofMaskAndCalcCocParam.blendState->Release();
		}

		m_downSampligCocAndColorParam.vs.Release();
		m_downSampligCocAndColorParam.ps.Release();
		for (auto& rt : m_downSampligCocAndColorParam.downSamplingRt) {
			rt.Release();
		}
	}
	void CDof::Init(const SGraphicsConfig& config)
	{
		if (config.dofConfig.isEnable==false) {
			return;
		}
		m_isEnable = config.dofConfig.isEnable;
		//����B
		Release();

		//�V�F�[�_�[���������B
		InitShaders();
		//�����_�����O�^�[�Q�b�g���������B
		InitRenderTargets();
		//�T���v���X�e�[�g�̏������B
		InitSamplerStates();
		//�萔�o�b�t�@�̏������B
		InitConstantBuffers();
	}
	void CDof::InitConstantBuffers()
	{
		m_createDofMaskAndCalcCocParam.cb.Create(nullptr, sizeof(SCreateDofMaskAndCalcCoc));
		m_downSampligCocAndColorParam.cb.Create(nullptr, sizeof(SDownSamplingCocAndColorCB));
	}
	void CDof::InitSamplerStates()
	{
		CD3D11_DEFAULT def;
		CD3D11_SAMPLER_DESC desc(def);
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		m_createDofMaskAndCalcCocParam.samplerState.Create(desc);

		m_finalParam.pointSamplerState = &m_createDofMaskAndCalcCocParam.samplerState;
	}
	void CDof::InitShaders()
	{
		m_createDofMaskAndCalcCocParam.vs.Load(
			"shader/dof/dof_CreateDofMaskAndCalcCoc.fx",
			"VSMain",
			CShader::EnType::VS);
		m_createDofMaskAndCalcCocParam.ps.Load(
			"shader/dof/dof_CreateDofMaskAndCalcCoc.fx",
			"PSMain",
			CShader::EnType::PS);

		m_downSampligCocAndColorParam.vs.Load(
			"shader/dof/dof_DownSamplingCocAndColor.fx",
			"VSMain",
			CShader::EnType::VS);

		m_downSampligCocAndColorParam.ps.Load(
			"shader/dof/dof_DownSamplingCocAndColor.fx",
			"PSMain",
			CShader::EnType::PS);

		m_finalParam.vs.Load(
			"shader/dof/dof_Final.fx",
			"VSMain",
			CShader::EnType::VS);
		m_finalParam.ps.Load(
			"shader/dof/dof_Final.fx",
			"PSMain",
			CShader::EnType::PS);
	}
	void CDof::InitRenderTargets()
	{
		auto& ge = GraphicsEngine();
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		//CoC�v�Z�p�̃����_�����O�^�[�Q�b�g���쐬����B
		m_createDofMaskAndCalcCocParam.calcCocAndColorRt.Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		);
		//�}�X�N�쐬�p�̃����_�����O�^�[�Q�b�g���쐬����B
		m_createDofMaskAndCalcCocParam.dofMaskRt.Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		);

		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
		for (int i = 0; i < NUM_DOWN_SAMPLING; i++) {
			m_downSampligCocAndColorParam.downSamplingRt[i].Create(
				ge.GetFrameBufferWidth() >> (i+1),
				ge.GetFrameBufferHeight() >> (i+1),
				1,
				1,
				DXGI_FORMAT_R16G16B16A16_FLOAT,
				DXGI_FORMAT_UNKNOWN,
				multiSampleDesc
			);
		}
	}
	void CDof::InitBlendStates()
	{
		auto d3dDevice = GraphicsEngine().GetD3DDevice();
		CD3D11_DEFAULT def;
		CD3D11_BLEND_DESC desc(def);

		//CoC���v�Z���郌���_�����O�^�[�Q�b�g�̓A���t�@�u�����f�B���O�̓I�t�B
		desc.RenderTarget[0].BlendEnable = false;
		//Dof�}�X�N���쐬���郌���_�����O�^�[�Q�b�g���A���t�@�u�����f�B���O�̓I�t�B
		desc.RenderTarget[1].BlendEnable = false;

		d3dDevice->CreateBlendState(&desc, &m_createDofMaskAndCalcCocParam.blendState);
	}
	void CDof::Update()
	{
	}
	void CDof::CreateDofMaskAndCalcCoc(CRenderContext& rc, CPostEffect* postEffect)
	{
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof::CreateDofMaskAndCalcCoc");
		//�V�[�����������܂�Ă��郌���_�����O�^�[�Q�b�g���擾����B
		auto& sceneRt = postEffect->GetFinalRenderTarget();
		auto& calcCocAndColorRt = m_createDofMaskAndCalcCocParam.calcCocAndColorRt;
		auto& dofMaskRt = m_createDofMaskAndCalcCocParam.dofMaskRt;
		auto& vs = m_createDofMaskAndCalcCocParam.vs;
		auto& ps = m_createDofMaskAndCalcCocParam.ps;
		auto& cb = m_createDofMaskAndCalcCocParam.cb;
		auto& samplerState = m_createDofMaskAndCalcCocParam.samplerState;
		auto& depthTextureSrv = ge.GetGBufferRender().GetRenderTarget(enGBufferDepth).GetRenderTargetSRV();
		//�����_�����O�^�[�Q�b�g��؂�ւ���B
		CRenderTarget* rts[] = {
			&calcCocAndColorRt,
			&dofMaskRt
		};
		//�萔�o�b�t�@�̍X�V�B
		SCreateDofMaskAndCalcCocCB cbParam;
		cbParam.dofRange.x = m_nearStartDistance;
		cbParam.dofRange.y = m_nearEndDistance;
		cbParam.dofRange.z = m_farStartDistance;
		cbParam.dofRange.w = m_farEndDistance;

		//���C������������VRAM�Ƀf�[�^��]���B
		rc.UpdateSubresource(cb, &cbParam);
		//�萔�o�b�t�@�����W�X�^b0�ɐݒ肷��B
		rc.VSSetConstantBuffer(0, cb);
		rc.PSSetConstantBuffer(0, cb);
		rc.OMSetRenderTargets(2, rts );
		rc.PSSetShaderResource(0, sceneRt.GetRenderTargetSRV());
		rc.PSSetShaderResource(1, depthTextureSrv);
		rc.VSSetShader(vs);
		rc.IASetInputLayout(vs.GetInputLayout());
		rc.PSSetShader(ps);
		rc.RSSetViewport(
			0, 
			0, 
			static_cast<float>(calcCocAndColorRt.GetWidth()), 
			static_cast<float>(calcCocAndColorRt.GetHeight())
		);
		rc.PSSetSampler(0, samplerState);
		rc.OMSetBlendState(m_createDofMaskAndCalcCocParam.blendState, 0, 0xFFFFFFFF);
		
		postEffect->DrawFullScreenQuad(rc);

		//�����_�����O�^�[�Q�b�g���O���B
		rc.OMSetRenderTargets(2, nullptr);

		ge.EndGPUEvent();

	}
	void CDof::DownSamplingCocAndColor(CRenderContext& rc, CPostEffect* postEffect)
	{
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof::DownSamplingCocAndColor");

		CShaderResourceView* textures[NUM_DOWN_SAMPLING] = {
			&m_createDofMaskAndCalcCocParam.calcCocAndColorRt.GetRenderTargetSRV(),
			&m_downSampligCocAndColorParam.downSamplingRt[0].GetRenderTargetSRV(),
			&m_downSampligCocAndColorParam.downSamplingRt[1].GetRenderTargetSRV(),
		};
		rc.PSSetSampler(0, *CPresetSamplerState::sampler_clamp_clamp_clamp_linear);

		for (int i = 0; i < NUM_DOWN_SAMPLING; i++){
			auto& rt = m_downSampligCocAndColorParam.downSamplingRt[i];
			//�����_�����O�^�[�Q�b�g��؂�ւ���B
			CRenderTarget* rts[] = {
				&rt
			};
			rc.OMSetRenderTargets(1, rts);

			//�萔�o�b�t�@�̍X�V
			SDownSamplingCocAndColorCB cb;
			cb.invRenderTargetSize.x = 1.0f / rt.GetWidth();
			cb.invRenderTargetSize.y = 1.0f / rt.GetHeight();
			rc.UpdateSubresource(m_downSampligCocAndColorParam.cb, &cb);

			rc.VSSetConstantBuffer(0, m_downSampligCocAndColorParam.cb);
			rc.PSSetShaderResource(0, *textures[i]);
			rc.VSSetShader(m_downSampligCocAndColorParam.vs);
			rc.PSSetShader(m_downSampligCocAndColorParam.ps);
			rc.RSSetViewport(
				0,
				0,
				static_cast<float>(rt.GetWidth()),
				static_cast<float>(rt.GetHeight()));
			rc.IASetInputLayout(m_downSampligCocAndColorParam.vs.GetInputLayout());
			postEffect->DrawFullScreenQuad(rc);

		}
		ge.EndGPUEvent();
	}
	void CDof::Final(CRenderContext& rc, CPostEffect* postEffect)
	{
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof::Final");
		auto& rt = postEffect->GetFinalRenderTarget();
		CRenderTarget* rts[] = {
			&rt,
		};
		rc.OMSetRenderTargets(1, rts);
		rc.VSSetShader(m_finalParam.vs);
		rc.PSSetShader(m_finalParam.ps);
		rc.PSSetShaderResource(0, m_downSampligCocAndColorParam.downSamplingRt[2].GetRenderTargetSRV());
		rc.PSSetShaderResource(1, m_createDofMaskAndCalcCocParam.dofMaskRt.GetRenderTargetSRV());
		rc.PSSetShaderResource(2, m_createDofMaskAndCalcCocParam.calcCocAndColorRt.GetRenderTargetSRV());
		rc.PSSetShaderResource(3, m_downSampligCocAndColorParam.downSamplingRt[0].GetRenderTargetSRV());
		rc.PSSetShaderResource(4, m_downSampligCocAndColorParam.downSamplingRt[1].GetRenderTargetSRV());
		rc.PSSetShaderResource(5, m_downSampligCocAndColorParam.downSamplingRt[2].GetRenderTargetSRV());
		rc.PSSetSampler(0, *m_finalParam.pointSamplerState);
		rc.OMSetBlendState(AlphaBlendState::trans, 0, 0xFFFFFFFF);
		rc.PSSetSampler(1, *CPresetSamplerState::sampler_clamp_clamp_clamp_linear);
		rc.RSSetViewport(
			0,
			0,
			static_cast<float>(rt.GetWidth()),
			static_cast<float>(rt.GetHeight())
		);
		rc.IASetInputLayout(m_finalParam.vs.GetInputLayout());
		postEffect->DrawFullScreenQuad(rc);

		rc.OMSetBlendState(AlphaBlendState::disable, 0, 0xFFFFFFFF);
		ge.EndGPUEvent();
	}
	void CDof::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		if (m_isEnable == false) {
			return;
		}
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof");
		rc.SetRenderStep(enRenderStep_Dof);

		CreateDofMaskAndCalcCoc(rc, postEffect);

		DownSamplingCocAndColor(rc, postEffect);

		Final(rc, postEffect);

		ge.EndGPUEvent();
	}
}