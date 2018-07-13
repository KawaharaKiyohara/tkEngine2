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
		/*!
		*@brief �萔�o�b�t�@�B
		*@todo �����͒萔�o�b�t�@����
		*/
		struct SConstantBuffer {
			CMatrix mViewProjInv;		//!<�r���[�v���W�F�N�V�����s��̋t�s��B
			CMatrix mViewProj;			//!<�r���[�v���W�F�N�V�����s��B
			CVector4 cameraPos;			//!<�J�����̎��_�B
		};
		bool m_isEnable = false;		//!<�L���B
		CShader m_vsShader;				//!<���_�V�F�[�_�[�B
		CShader m_psShader;				//!<�s�N�Z���V�F�[�_�[�B
		CConstantBuffer m_cb;			//!<�萔�o�b�t�@�B
	};
}