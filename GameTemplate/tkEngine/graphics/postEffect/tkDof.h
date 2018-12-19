/// <summary>
/// DOF(��ʊE�[�x)
/// </summary>
#pragma once

namespace tkEngine {
	class CPostEffect;
	/// <summary>
	/// DOF(��ʊE�[�x)
	/// </summary>
	class CDof : Noncopyable {
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CDof();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CDof();
		/// <summary>
		/// ����B
		/// </summary>
		/// <remarks>
		/// �{�֐��̓f�X�g���N�^����Ăяo����Ă��邽�߁A�ʏ�
		/// �����I�ȃ^�C�~���O�Ń��\�[�X������������ꍇ�ɌĂяo���Ă��������B
		/// </remarks>
		void Release();
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="config">�O���t�B�b�N�ݒ�</param>
		void Init(const SGraphicsConfig& config);
		/// <summary>
		/// �X�V�B
		/// </summary>
		void Update();
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="postEffect">�|�X�g�G�t�F�N�g</param>
		void Render(CRenderContext& rc, CPostEffect* postEffect);
	private:
		/// <summary>
		/// �V�[���e�N�X�`���Ƀo�C���j�A�t�B���^�������āA�J�����ɋ߂�����CoC(�����~�̔��a)�̌v�Z���s���܂��B
		/// </summary>
		void ApplyBilinearFilterAndCalcNearCoc(CRenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �����_�����O�^�[�Q�b�g���������B
		/// </summary>
		void InitRenderTargets();
		/// <summary>
		/// �V�F�[�_�[���������B
		/// </summary>
		void InitShaders();
	private:
		bool m_isEnable = false;
		CRenderTarget m_cocAndColorRt;				//�s�N�Z����CoC�̌v�Z���ʂƃo�C���j�A�t�B���^���������J���[���`�����܂�郌���_�����O�^�[�Q�b�g�B
		CShader m_applyBinFilterAndCalcNearCocVS;	//
		CShader m_applyBinFilterAndCalcNearCocPS;
										
	};
}