/// <summary>
/// DOF(��ʊE�[�x
/// </summary>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkDof.h"
#include "tkEngine/graphics/tkPresetRenderState.h"

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
		m_cocAndColorRt.Release();
		m_applyBinFilterAndCalcNearCocVS.Release();
		m_applyBinFilterAndCalcNearCocPS.Release();
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
		
	}
	void CDof::InitShaders()
	{
		m_applyBinFilterAndCalcNearCocVS.Load(
			"shader/dof/dof_ApplyBinFilterAndCalcNearCoC.fx",
			"VSMain",
			CShader::EnType::VS);
		m_applyBinFilterAndCalcNearCocPS.Load(
			"shader/dof/dof_ApplyBinFilterAndCalcNearCoC.fx",
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
		//1/4�̉𑜓x�B�_�E���T���v�����O���s����B
		m_cocAndColorRt.Create(
			ge.GetFrameBufferWidth() / 2,
			ge.GetFrameBufferHeight() / 2,
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		);
	}
	void CDof::Update()
	{
	}
	void CDof::ApplyBilinearFilterAndCalcNearCoc(CRenderContext& rc, CPostEffect* postEffect)
	{
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof::ApplyBilinearFilterAndCalcNearCoc");
		//�V�[�����������܂�Ă��郌���_�����O�^�[�Q�b�g���擾����B
		auto& sceneRt = postEffect->GetFinalRenderTarget();
		//�����_�����O�^�[�Q�b�g��؂�ւ���B
		CRenderTarget* rts[] = {
			&m_cocAndColorRt
		};
		rc.OMSetRenderTargets(1, rts );
		rc.PSSetShaderResource(0, sceneRt.GetRenderTargetSRV());
		rc.VSSetShader(m_applyBinFilterAndCalcNearCocVS);
		rc.IASetInputLayout(m_applyBinFilterAndCalcNearCocVS.GetInputLayout());
		rc.PSSetShader(m_applyBinFilterAndCalcNearCocPS);
		rc.RSSetViewport(0, 0, m_cocAndColorRt.GetWidth(), m_cocAndColorRt.GetHeight());
		postEffect->DrawFullScreenQuad(rc);

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
		//�V�[���e�N�X�`���Ƀo�C���j�A�t�B���^�������āA
		//�J�����ɋ߂�����CoC(�����~�̔��a)�̌v�Z���s���܂��B
		ApplyBilinearFilterAndCalcNearCoc(rc, postEffect);

		ge.EndGPUEvent();
	}
}