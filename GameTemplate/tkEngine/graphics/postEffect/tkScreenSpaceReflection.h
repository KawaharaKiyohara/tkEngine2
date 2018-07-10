/*!
 *@brief	Screen Space Reflection
 */

#pragma once

namespace tkEngine{
	class CPostEffect;
	/*!
	*@brief	Screen Space Reflection
	*@details
	* �X�N���[����ԂŃ��C�}�[�`���O���s���^���I�ȉf�荞�݂�\�����܂��B
	*/
	class CScreenSpaceReflection{
	public:
		/*!
		*@brief	�J���B
		*/
		void Release();
		/*!
		*@brief	�������B
		*/
		void Init(const SGraphicsConfig& config);
		/*!
		*@brief	�`��B
		*@param[in]		rc		�����_�����O�R���e�L�Xt�B
		*/
		void Render(CRenderContext& rc, CPostEffect* postEffect);
	private:
		bool m_isEnable = false;		//!<�L���B
		CShader m_vsShader;				//!<���_�V�F�[�_�[�B
		CShader m_psShader;				//!<�s�N�Z���V�F�[�_�[�B

	};
}