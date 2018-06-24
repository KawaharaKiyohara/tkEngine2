/*!
 * @brief	G-Bufferの描画。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkGBufferRender.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"


//#define ENABLE_G_BUFFER_MSAA  //定義するとG-BufferにMSAAがかかる。
namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CGBufferRender::CGBufferRender()
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CGBufferRender::~CGBufferRender()
	{
	}
	/*!
	*@brief	初期化。
	*/
	void CGBufferRender::Init(const SGraphicsConfig& config)
	{
#ifndef ENABLE_G_BUFFER_MSAA
		CGraphicsEngine& ge = GraphicsEngine();

		DXGI_SAMPLE_DESC msaaDesc;
		ZeroMemory(&msaaDesc, sizeof(msaaDesc));
		msaaDesc.Count = 1;
		msaaDesc.Quality = 0;

		//アルベドバッファの初期化。
		m_GBuffer[enGBufferAlbedo].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			msaaDesc
		);
		m_GBuffer[enGBufferAlbedo].SetDepthStencilView(
			ge.GetMainRenderTarget().GetDepthStencilView()
		);
		//法線バッファの初期化。
		m_GBuffer[enGBufferNormal].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
		//接ベクトルバッファの初期化。
		m_GBuffer[enGBufferTangent].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
		//スペキュラバッファの初期化。
		m_GBuffer[enGBufferSpecular].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
		//影マップの初期化。
		m_GBuffer[enGBufferShadow].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);

		//深度バッファの初期化。
		m_GBuffer[enGBufferDepth].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
#else
		//こっちが有効だとG-BufferにMSAAがかかる。
		CGraphicsEngine& ge = GraphicsEngine();
		//アルベドバッファの初期化。
		m_GBuffer[enGBufferAlbedo].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			ge.GetMainRenderTargetMSAADesc()
		);
		//法線バッファの初期化。
		m_GBuffer[enGBufferNormal].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			ge.GetMainRenderTargetMSAADesc()
		);
		//接ベクトルバッファの初期化。
		m_GBuffer[enGBufferTangent].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			ge.GetMainRenderTargetMSAADesc()
		);
		//スペキュラバッファの初期化。
		m_GBuffer[enGBufferSpecular].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			ge.GetMainRenderTargetMSAADesc()
		);
		//影マップの初期化。
		m_GBuffer[enGBufferShadow].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			ge.GetMainRenderTargetMSAADesc()
		);

		//深度バッファの初期化。
		m_GBuffer[enGBufferDepth].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			ge.GetMainRenderTargetMSAADesc()
		);
#endif
		m_shadowBlur.Init(m_GBuffer[enGBufferShadow].GetRenderTargetSRV(), 5.0f, config.shadowRenderConfig);
		
		m_cb.Create(NULL, sizeof(m_cbEntity));
	}
	
	void CGBufferRender::SetGBufferParamToReg(CRenderContext& rc)
	{
		rc.PSSetShaderResource(enSkinModelSRVReg_AlbedoTexture, m_GBuffer[enGBufferAlbedo].GetRenderTargetSRV() );
		rc.PSSetShaderResource(enSkinModelSRVReg_NormalMap, m_GBuffer[enGBufferNormal].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSKinModelSRVReg_Specularmap, m_GBuffer[enGBufferSpecular].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSkinModelSRVReg_DepthMap, m_GBuffer[enGBufferDepth].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSkinModelSRVReg_Tangent, m_GBuffer[enGBufferTangent].GetRenderTargetSRV());
		if (GraphicsEngine().GetShadowMap().GetSoftShadowLevel() == EnSoftShadowQualityLevel::enNone) {
			//ハードシャドウ。
			rc.PSSetShaderResource(enSkinModelSRVReg_SoftShadowMap, m_GBuffer[enGBufferShadow].GetRenderTargetSRV());
		}
		else {
			//ソフトシャドウ
			rc.PSSetShaderResource(enSkinModelSRVReg_SoftShadowMap, m_shadowBlur.GetResultSRV());
		}
	}
	void CGBufferRender::UnsetGBufferParamFromReg(CRenderContext& rc)
	{
		rc.PSUnsetShaderResource(enSkinModelSRVReg_AlbedoTexture);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_NormalMap);
		rc.PSUnsetShaderResource(enSKinModelSRVReg_Specularmap);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_DepthMap);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_Tangent);
		
		if (GraphicsEngine().GetShadowMap().GetSoftShadowLevel() == EnSoftShadowQualityLevel::enNone) {
			//ハードシャドウ。
			rc.PSUnsetShaderResource(enSkinModelSRVReg_SoftShadowMap);
		}
		else {
			//ソフトシャドウ
			rc.PSUnsetShaderResource(enSkinModelSRVReg_SoftShadowMap);
		}
	}
	void CGBufferRender::Render(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_RenderGBuffer");
		EnSoftShadowQualityLevel ssLevel = GraphicsEngine().GetShadowMap().GetSoftShadowLevel();

		//影を落とすための情報を転送。
		GraphicsEngine().GetShadowMap().SendShadowReceiveParamToGPU(rc);

		rc.SetRenderStep(enRenderStep_RenderGBuffer);

		m_cbEntity.isPCFShadowMap = ssLevel == EnSoftShadowQualityLevel::eSSSS_PCF;
		rc.UpdateSubresource(m_cb, &m_cbEntity);

		rc.PSSetConstantBuffer(enSkinModelCBReg_GBuffer, m_cb);
		//レンダリングターゲットのバックアップを取得する。
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);

		//レンダリングターゲットを変更する。
		CRenderTarget* renderTargets[enGBufferNum];
		for( int i = 0; i < enGBufferNum ; i++ ){
			renderTargets[i] = &m_GBuffer[i];
		};
		rc.OMSetRenderTargets(enGBufferNum, renderTargets);
		//Gバッファをクリア。
		float clearColor[enGBufferNum][4] = { 
			{ 0.5f, 0.5f, 0.5f, 1.0f }, //enGBufferAlbedo
			{ 0.0f, 1.0f, 0.0f, 1.0f }, //enGBufferNormal
			{ 0.0f, 0.0f, 0.0f, 1.0f }, //enGBufferSpecular
			{ 0.0f, 0.0f, 0.0f, 1.0f }, //enGBufferShadow
			{ 1.0f, 1.0f, 1.0f, 1.0f },	//enGBufferDepth
			{ 1.0f, 0.0f, 0.0f, 1.0f },	//enGBufferTangent
		};
		
		for (int i = 0; i < enGBufferNum; i++) {
			rc.ClearRenderTargetView(i, clearColor[i]);
		}

		for (auto& skinModel : m_skinModels) {
			skinModel->Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		}
#ifdef ENABLE_G_BUFFER_MSAA
		//MSAAリゾルブ。
		for (auto& rt : renderTargets) {
			rt->ResovleMSAATexture(rc);
		}
#endif
		if (ssLevel == EnSoftShadowQualityLevel::eSSSS
			|| ssLevel == EnSoftShadowQualityLevel::eSSSS_PCF
		) {
			//スクリーンスペースソフトシャドウ。
			//影マップにブラーをかける。
			m_shadowBlur.Execute(rc);
		}

		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		m_skinModels.clear();

		EndGPUEvent();
	}
}