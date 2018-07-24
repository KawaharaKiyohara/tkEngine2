/*!
 *@brief	�t�H���g�m�[�h�B
 */

#pragma once

#include "tkEngine/HUD/tkIHUDNode.h"

namespace tkEngine{
	class CHUDNode_Font : public IHUDNode{
	public:
		CHUDNode_Font(CBone* bone);
		void Update() override;
		void PostRender( CRenderContext& rc ) override;
		/*!
		*@brief	�e�L�X�g��ݒ�B
		*/
		void SetText(const wchar_t* text)
		{
			m_text = text;
		}
	private:
		std::unique_ptr<CFont>	m_font;
		std::wstring m_text;
		CVector2 m_position = CVector2::Zero;
	};
}