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
		/// <summary>
		/// ��ʊE�[�x�͈̔͂ɉe������p�����[�^��ݒ�B
		/// </summary>
		/// <param name="nearStartDistance">��O�{�P�̌������J�n����J��������̋���</param>
		/// <param name="nearEndDistance">��O�{�P�̌������I������J��������̋���</param>
		/// <param name="farStartDistance">���{�P�̑������J�n����J��������̋���</param>
		/// <param name="farEndDistance">���{�P�̑������I������J��������̋���</param>
		/// <remarks>
		/// 
		///                      nearStartDistance          nearEndDistance         farStartDistance    �@�@farEndDistance
		///�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ |�@�@�@�@�@�@�@�@�@�@�@�@  |                    |                      |
		/// �@�@�@�@�@�����͍ő�̎�O�@�@|��O�{�P���������Ă���@�@|��ʊE�[�x�� �B     |���{�P���������Ă���@|����������͍ő�̉��{�P��
		///�@�@�@�@�@�@�{�P���������Ă��� |�@�@�@�@�@�@�@�@�@�@�@�@�@|�{�P���������Ă��Ȃ�|                    �@|�������Ă���
		/// �J�����|���Q�Q�Q�Q�Q�Q�Q�Q�Q�Q|�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q|____________________|____________________�Q|________________�Q�Q�Q�Q�Q�Q�Q�Q
		/// 
		/// </remarks>
		void SetDofRangeParam(float nearStartDistance, float nearEndDistance, float farStartDistance, float farEndDistance)
		{
			//�y�d�v�I�I�I�I�I�z
			//end�͕K��start���傫���Ȃ邱�Ƃ�ۏ؂���悤�ɁI
			//�����ۏ؂��Ȃ��Ȃ�ƁA�V�F�[�_�[����0���Z����������\�������܂�܂��B
			m_nearStartDistance = std::max<float>(0.0f, nearStartDistance);
			m_nearEndDistance = std::max<float>(m_nearStartDistance + 0.001f, nearEndDistance);
			m_farStartDistance = std::max<float>(m_nearEndDistance + 0.001f, farStartDistance);
			m_farEndDistance = std::max<float>(m_farStartDistance + 0.001f, farEndDistance);
		}
	private:
		/// <summary>
		/// �s�N�Z���P�ʂ�Dof�}�X�N�̍쐬��Coc�̌v�Z���s���`��p�X�B
		/// </summary>
		void CreateDofMaskAndCalcCoc(CRenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �V�[���̃J���[����CoC���̃_�E���T���v�����O���s���`��p�X�B
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="postEffect"></param>
		void DownSamplingCocAndColor(CRenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �ŏI�V�[�������̕`��p�X�B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="postEffect">�|�X�g�G�t�F�N�g</param>
		void Final(CRenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �����_�����O�^�[�Q�b�g���������B
		/// </summary>
		void InitRenderTargets();
		/// <summary>
		/// �V�F�[�_�[���������B
		/// </summary>
		void InitShaders();
		/// <summary>
		/// �T���v���X�e�[�g�̏������B
		/// </summary>
		void InitSamplerStates();
		/// <summary>
		/// �萔�o�b�t�@�̏������B
		/// </summary>
		void InitConstantBuffers();
		/// <summary>
		/// �u�����f�B���O�X�e�[�g������������B
		/// </summary>
		void InitBlendStates();
	private:
		/// <summary>
		/// CreateDofMaskAndCalcCoc�̃p�X�Ŏg�p����萔�o�b�t�@�̍\���́B
		/// </summary>
		/// <remarks>
		/// ���̍\���̂̒��g��ύX������AAssets/shader/dof/dof_CreateDofMaskAndCalcCoc.fx��
		/// cbParam�̓��e���ύX����B
		/// </remarks>
		struct SCreateDofMaskAndCalcCocCB {
			CVector4 dofRange;				//��ʊE�[�x�͈̔͂�\���f�[�^�BSetDofRangeParam�֐��Őݒ肳���f�[�^�B
											//x�͎�O�{�P�̌������J�n����J��������̋����B
											//y�͎�O�{�P�̌������I������J��������̋����B
											//z�͉��{�P�̑������J�n����J��������̋����B
											//w�͉��{�P�̑������I������J��������̋����B			
		};
		/// <summary>
		/// CreateDofMaskAndCalcCoc�̃p�X�Ŏg�p����f�[�^�W�B
		/// </summary>
		struct SCreateDofMaskAndCalcCoc {
			CRenderTarget calcCocAndColorRt;			//�s�N�Z����CoC�̌v�Z���ʂ��`�����܂�郌���_�����O�^�[�Q�b�g�BCoC�̓��`�����l���ɏ������܂�܂��B
			CRenderTarget dofMaskRt;					//��ʊE�[�x���̃s�N�Z����\���}�X�N�B0��1��2�l�����ꂽ�f�[�^�B0�͔�ʊE�[�x���̃s�N�Z���Ȃ̂Ń{�P�Ȃ��B
			CShader vs;									//���_�V�F�[�_�[�B
			CShader ps;									//�s�N�Z���V�F�[�_�[�B
			CSamplerState	samplerState;				//�T���v���X�e�[�g�B
			ID3D11BlendState* blendState = nullptr;		//�A���t�@�u�����f�B���O�X�e�[�g�B
			CConstantBuffer cb;							//�萔�o�b�t�@�B
		};
		//�_�E���T���v�����O�̉�
		static const int NUM_DOWN_SAMPLING = 4;
		/// <summary>
		/// DownSamplingCocAndColorCB�̃p�X�Ŏg�p����萔�o�b�t�@�̍\���́B
		/// </summary>
		/// <remarks>
		/// ���̍\���̂̒��g��ύX������AAssets/shader/dof/dof_DownSamplingCocAndColor.fx��
		/// cbParam�̓��e���ύX����B
		/// </remarks>
		struct SDownSamplingCocAndColorCB {
			CVector2 invRenderTargetSize;	//�����_�����O�^�[�Q�b�g�̋t���B
		};
		/// <summary>
		/// CoC�̏��ƃV�[���J���[�̉摜���_�E���T���v�����O���Ă������Ɏg�p����f�[�^�W�B
		/// </summary>
		struct SDownSamplingCocAndColor {
			CRenderTarget downSamplingRt[NUM_DOWN_SAMPLING];
			CShader vs;
			CShader ps;
			CConstantBuffer cb;
		};
		/// <summary>
		/// �ŏI�����̃p�X�Ŏg�p����f�[�^�B
		/// </summary>
		struct SFinal {
			CShader vs;
			CShader ps;
			CSamplerState* pointSamplerState = nullptr;	//SCreateDofMaskAndCalcCoc��samplerState���g�킹�Ă��������B
		};
		bool m_isEnable = false;	//Dof���L�����ǂ����̃t���O�B
		SCreateDofMaskAndCalcCoc m_createDofMaskAndCalcCocParam;
		SDownSamplingCocAndColor m_downSampligCocAndColorParam;
		SFinal m_finalParam;

		float m_nearStartDistance = 0.0f;		//��O�{�P�̌������J�n����J��������̋����B
		float m_nearEndDistance = 150.0f;		//��O�{�P�̌������I������J��������̋����B
		float m_farStartDistance = 200.0f;		//���{�P�̑������J�n����J��������̋����B
		float m_farEndDistance = 500.0f;		//���{�P�̑������I������J��������̋����B
	};
}