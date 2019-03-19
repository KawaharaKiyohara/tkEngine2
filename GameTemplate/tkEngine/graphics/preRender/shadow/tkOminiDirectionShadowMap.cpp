/*!
 * @brief	�V���h�E�}�b�v�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/shadow/tkOminiDirectionShadowMap.h"
#include "tkEngine/graphics/preRender/shadow/tkShadowCaster.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine {

	COminiDirectionShadowMap::COminiDirectionShadowMap()
	{
	}

	COminiDirectionShadowMap::~COminiDirectionShadowMap()
	{
		if (m_shadowMap != nullptr) {
			m_shadowMap->Release();
		}
		for (auto& rt : m_renderTargets) {
			rt->Release();
		}
		if (m_depthStencilTexture != nullptr) {
			m_depthStencilTexture->Release();
		}
		if (m_depthStencilView != nullptr) {
			m_depthStencilView->Release();
		}
	}
	bool COminiDirectionShadowMap::InitShadowMapTextures(ID3D11Device* pD3DDevice)
	{
		m_texDesc.Width = 512;
		m_texDesc.Height = 512;
		m_texDesc.MipLevels = 0;
		m_texDesc.ArraySize = NUM_TEXTURE;
		m_texDesc.Format = DXGI_FORMAT_R32_FLOAT;
		m_texDesc.SampleDesc.Count = 1;
		m_texDesc.SampleDesc.Quality = 0;
		m_texDesc.Usage = D3D11_USAGE_DEFAULT;
		m_texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		m_texDesc.CPUAccessFlags = 0;
		m_texDesc.MiscFlags = 0;

		auto hr = pD3DDevice->CreateTexture2D(&m_texDesc, nullptr, &m_shadowMap);
		if (FAILED(hr)) {
			//�L���[�u�}�b�v�̍쐬�Ɏ��s�B
			return false;
		}
		return true;
	}
	bool COminiDirectionShadowMap::InitRenderTargetViews(ID3D11Device* pD3DDevice)
	{
		//�����_�����O�^�[�Q�b�g�r���[���쐬����B
		D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
		ZeroMemory(&rtDesc, sizeof(rtDesc));
		rtDesc.Format = m_texDesc.Format;
		rtDesc.Texture2DArray.ArraySize = NUM_TEXTURE;
		for (int i = 0; i < NUM_TEXTURE; i++) {
			rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtDesc.Texture2DArray.FirstArraySlice = i;
			auto hr = pD3DDevice->CreateRenderTargetView(
				m_shadowMap, &rtDesc, &m_renderTargets[i]);
			if (FAILED(hr)) {
				//�����_�����O�^�[�Q�b�g�r���[�̍쐬�Ɏ��s�����B
				return false;
			}
		}
		return true;
	}
	bool COminiDirectionShadowMap::InitDepthStencilTextures(ID3D11Device* pD3DDevice)
	{
		m_depthTexDesc = m_texDesc;
		m_depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		m_depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		auto hr = pD3DDevice->CreateTexture2D(&m_depthTexDesc, nullptr, &m_depthStencilTexture);
		if (FAILED(hr)) {
			return false;
		}
		return true;
	}
	bool COminiDirectionShadowMap::InitDepthStencilViews(ID3D11Device* pD3DDevice)
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {0};
		descDSV.Format = m_depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		auto hr = pD3DDevice->CreateDepthStencilView(
			m_depthStencilTexture, &descDSV, &m_depthStencilView
		);
		if (FAILED(hr)) {
			return false;
		}
		return true;
	}
	bool COminiDirectionShadowMap::Init(const SOminiShadowRenderConfig& config)
	{
		auto pD3DDevice = GraphicsEngine().GetD3DDevice();
		
		//�V���h�E�}�b�v�`��p�̃e�N�X�`�����쐬����B
		if (InitShadowMapTextures(pD3DDevice) == false) {
			//�V���h�E�}�b�v�p�̃e�N�X�`���̍쐬�Ɏ��s�B
			return false;
		}
		//�����_�����O�^�[�Q�b�g�r���[���쐬�B
		if (InitRenderTargetViews(pD3DDevice) == false) {
			//�����_�����O�^�[�Q�b�g�r���[�̍쐬�Ɏ��s�B
			return false;
		}
		//�f�v�X�X�e���V���e�N�X�`�����쐬����B
		if (InitDepthStencilTextures(pD3DDevice) == false) {
			return false;
		}
		//�f�v�X�X�e���V���r���[���쐬����B
		if (InitDepthStencilViews(pD3DDevice) == false) {
			return false;
		}
		return true;
	}

	void COminiDirectionShadowMap::Update()
	{
		
	}
	
	void COminiDirectionShadowMap::RenderToShadowMapImp(CRenderContext& rc)
	{
		static const CVector3 cameraDirectionTbl[NUM_TEXTURE] = {
			{ 1.0f,  0.0f,  0.0f },	//POSITIVE_X
			{-1.0f,  0.0f,  0.0f },	//NEGATIVE_X
			{ 0.0f,  1.0f,  0.0f },	//POSITIVE_Y
			{ 0.0f, -1.0f,  0.0f },	//NEGATIVE_Y
			{ 0.0f,  0.0f,  1.0f },	//POSITIVE_Z
			{ 0.0f,  0.0f, -1.0f },	//NEGATIVE_Z
		};
		static const CVector3 cameraUpTbl[NUM_TEXTURE] = {
			{ 0.0f,  1.0f,  0.0f },	//POSITIVE_X
			{ 0.0f,  1.0f,  0.0f },	//NEGATIVE_X
			{ 0.0f,  0.0f,  1.0f },	//POSITIVE_Y
			{ 0.0f,  0.0f,  1.0f },	//NEGATIVE_Y
			{ 0.0f,  1.0f,  0.0f },	//POSITIVE_Z
			{ 0.0f,  1.0f,  0.0f },	//NEGATIVE_Z
		};
		for (int i = 0; i < NUM_TEXTURE; i++) {
			//�J�����s����쐬����B
			CMatrix mView;
			mView.MakeLookAt(
				m_lightPosition,
				m_lightPosition + cameraDirectionTbl[i],
				cameraUpTbl[i] );
			//�ˉe�s����쐬����B
			CMatrix mProj;
			mProj.MakeProjectionMatrix(
				CMath::DegToRad(90.0f),
				1.0f,
				0.0f,
				m_distanceAffectedByLight
			);
			CMatrix mLightViewProjection;
			mLightViewProjection = mView * mProj;
		}
	}
	void COminiDirectionShadowMap::SendShadowReceiveParamToGPU(CRenderContext& rc)
	{
	}
}