/*!
 * @brief	��ʊE�[�x�p�̃u���[�B
 */

#pragma once

#include "tkEngine/graphics/tkBlur.h"

namespace tkEngine{
	/*!
	 * @brief	��ʊE�[�x�p�̃u���[�B
	 */
	class CDofBlur : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CDofBlur();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CDofBlur();
		/*!
		 * @brief	�������B
		 *@param[in]	srcTexture		���e�N�X�`���B
		 *@param[in]	blurIntensity	�u���[�̋����B�l���傫���قǃ{�P��B
		 */
		void Init( CShaderResourceView& srcTexture, float blurIntensity = 25.0f );
		
		/*!
		 * @brief	�u���[�����s�B
		 */
		void Execute(CRenderContext& rc);
		/*!
		* @brief	���s���ʂ��i�[���Ă���SRV���擾�B
		*/
		CShaderResourceView& GetResultSRV()
		{
			return m_blur.GetResultSRV();
		}
	
	private:
	
		CShader m_vsXBlurShader;			//!<X�u���[�p�̒��_�V�F�[�_�[�B
		CShader m_vsYBlurShader;			//!<Y�u���[�p�̒��_�V�F�[�_�[�B
		CShader m_psBlurShader;				//!<�u���[�p�̃s�N�Z���V�F�[�_�[�B
		CBlur m_blur;						//!<�K�E�V�A���u���[�B
	};
}