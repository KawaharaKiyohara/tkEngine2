/*!
 * @brief	G-Bufferを描画。
 */

#pragma once

#include "tkEngine/graphics/tkShadowBlur.h"

namespace tkEngine{
	//!<G-Bufferの定義。
	enum EnGBuffer{
		enGBufferAlbedo,	//!<アルベド。
		enGBufferNormal,	//!<法線。
		enGBufferSpecular,	//!<スペキュラ。
		enGBufferShadow,	//!<影マップ。
		enGBufferDepth,		//!<深度。
		enGBufferTangent,	//!<接法線。
		enGBufferNum,		//!<G-Bufferの数。
	};
	/*!
	 * @brief	G-Buffer。
	 */
	class CGBufferRender : Noncopyable{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CGBufferRender();
		/*!
		 * @brief	デストラクタ。
		 */
		~CGBufferRender();
		/*!
		 *@brief	初期化。
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		*@brief	スキンモデルを追加。
		*/
		void AddSkinModel(CSkinModel* skinModel)
		{
			m_skinModels.push_back(skinModel);
		}
		/*!
		 * @brief	描画。
		 */
		void Render(CRenderContext& rc);
		/*!
		*@brief	GBufferのパラメータをレジスタに設定。
		*/
		void SetGBufferParamToReg(CRenderContext& rc);
		/*!
		*@brief	GBufferをレジスタから外す。
		*/
		void UnsetGBufferParamFromReg(CRenderContext& rc);
		/*!
		*@brief	GBufferを取得。
		*@param[in]	enGBuffer	取得したいG-Buffer
		*/
		CRenderTarget& GetRenderTarget(EnGBuffer enGBuffer) 
		{
			return m_GBuffer[enGBuffer];
		}
	private:
		
		//定数パラメータ。
		struct SCBParam {
			bool isPCFShadowMap;		//影マップを作るときにPCFを行う。
		};
		std::vector<CSkinModel*>	m_skinModels;	//!<スキンモデルのリスト。
		CRenderTarget m_GBuffer[enGBufferNum];		//!<G-Buffer
		CShadowBlur m_shadowBlur;					//!<影マップへのブラー処理。
		SCBParam m_cbEntity;
		CConstantBuffer m_cb;
	};
}
