/// <summary>
/// DOF(��ʊE�[�x)
/// </summary>
#pragma once

#include "tkEngine/graphics/postEffect/tkDofBlur.h"

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
		void GetDofRangeParam(float& nearStartDistance, float& nearEndDistance, float& farStartDistance, float& farEndDistance)
		{
			nearStartDistance = m_nearStartDistance;
			nearEndDistance = m_nearEndDistance;
			farStartDistance = m_farStartDistance;
			farEndDistance = m_farEndDistance;
		}
		/// <summary>
		/// DoF��L���ɂ���B
		/// </summary>
		void Enable()
		{
			m_isEnable = true;
		}
		/// <summary>
		/// DoF�𖳌��ɂ���B
		/// </summary>
		void Disable()
		{
			m_isEnable = false;
		}
	private:
		/// <summary>
		/// �����~�e�N�X�`���̍쐬�s���`��p�X�B
		/// </summary>
		void CreateCoCTexture(CRenderContext& rc, CPostEffect* postEffect);
		/// <summary>
		/// �{�P�摜�̍쐬���s���`��p�X�B
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="postEffect"></param>
		void CreateBokeTexture(CRenderContext& rc, CPostEffect* postEffect);
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
		/// �萔�o�b�t�@�̏������B
		/// </summary>
		void InitConstantBuffers();
		/// <summary>
		/// �u�����f�B���O�X�e�[�g������������B
		/// </summary>
		void InitBlendStates();
		
	private:
		/// <summary>
		/// CreateCoc�̃p�X�Ŏg�p����萔�o�b�t�@�̍\���́B
		/// </summary>
		/// <remarks>
		/// ���̍\���̂̒��g��ύX������AAssets/shader/dof/dof_CreateCoc.fx��
		/// cbParam�̓��e���ύX����B
		/// </remarks>
		struct SCreateCocParamCB {
			CVector4 dofRange;				//��ʊE�[�x�͈̔͂�\���f�[�^�BSetDofRangeParam�֐��Őݒ肳���f�[�^�B
											//x�͎�O�{�P�̌������J�n����J��������̋����B
											//y�͎�O�{�P�̌������I������J��������̋����B
											//z�͉��{�P�̑������J�n����J��������̋����B
											//w�͉��{�P�̑������I������J��������̋����B			
		};
		/// <summary>
		/// CreateCoCTexture�̃p�X�Ŏg�p����f�[�^�W�B
		/// </summary>
		struct SCreateCoCTexture {
			CRenderTarget calcCocAndColorRt;			//�s�N�Z����CoC�̌v�Z���ʂ��`�����܂�郌���_�����O�^�[�Q�b�g�BCoC�̓��`�����l���ɏ������܂�܂��B
			CShader vs;									//���_�V�F�[�_�[�B
			CShader ps;									//�s�N�Z���V�F�[�_�[�B
			ID3D11BlendState* blendState = nullptr;		//�A���t�@�u�����f�B���O�X�e�[�g�B
			CConstantBuffer cb;							//�萔�o�b�t�@�B
		};
		//�_�E���T���v�����O�̉�
		static const int NUM_DOWN_SAMPLING = 2;
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
			CDofBlur blur;		 //todo Release�֐����Ȃ����B						//�u���[�B
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
		};
		bool m_isEnable = false;	//Dof���L�����ǂ����̃t���O�B
		SCreateCoCTexture m_createCocParam;
		SDownSamplingCocAndColor m_downSampligCocAndColorParam;
		SFinal m_finalParam;

		float m_nearStartDistance = 0.0f;		//��O�{�P�̌������J�n����J��������̋����B
		float m_nearEndDistance = 150.0f;		//��O�{�P�̌������I������J��������̋����B
		float m_farStartDistance = 200.0f;		//���{�P�̑������J�n����J��������̋����B
		float m_farEndDistance = 500.0f;		//���{�P�̑������I������J��������̋����B
	};
}