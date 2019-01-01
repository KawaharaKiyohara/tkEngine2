/*!
 *@brief	�����_�����O�^�[�Q�b�g�؂�ւ��̃w���p�[�N���X�B
 */

#pragma once

namespace tkEngine{
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�؂�ւ��N���X�B
	/// </summary>
	class CChangeRenderTarget {
	public:
		CChangeRenderTarget(CRenderContext& rc, CRenderTarget& rt)
		{
			CRenderTarget* rts[] = {
				&rt
			};
			rc.OMSetRenderTargets(1, rts);
			rc.RSSetViewport(0.0f, 0.0f, (float)rts[0]->GetWidth(), (float)rts[0]->GetHeight());
		}
		~CChangeRenderTarget()
		{
		}
	};
}