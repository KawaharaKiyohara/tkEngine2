/*!
 * @brief	�X�L�����f�������_���[
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelRender.h"


namespace tkEngine{
namespace prefab{
	/*!
	 * @brief	�R���X�g���N�^�B
	 *@param[in]	filePath	�t�@�C���p�X�B
	 */
	CSkinModelRender::CSkinModelRender(
		const wchar_t* filePath, 
		CAnimationClip* animationClips, 
		int numAnimationClips,
		CSkinModel::EnFbxUpAxis fbxUpAxis
	) :
		m_filePath(filePath),
		m_animationClips(animationClips),
		m_numAnimationClips(numAnimationClips),
		m_enFbxUpAxis(fbxUpAxis)
	{
		m_skinModelData.Load(m_filePath.c_str());
		m_skinModel.Init(m_skinModelData);
		InitAnimation(animationClips, numAnimationClips);
	}
	void CSkinModelRender::InitAnimation(CAnimationClip* animationClips, int numAnimationClips)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skinModel, m_animationClips, m_numAnimationClips);
		}
	}
	/*!
	 * @brief	�X�V�O�ɌĂ΂��֐��B
	 */
	bool CSkinModelRender::Start() 
	{
		return true;
	}
	/*!
	 * @brief	�X�V�B
	 */
	void CSkinModelRender::Update()
	{
		m_skinModel.Update(m_position, m_rotation, m_scale, m_enFbxUpAxis);
	}
	/*!
	 * @brief	�`��B
	 */
	void CSkinModelRender::Render(CRenderContext& rc)
	{
		m_skinModel.Draw(rc);
	}
}
}