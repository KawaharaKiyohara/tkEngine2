/*!
 * @brief	�v���C���[�����_���[
 *@details
 * �v���C���[�̕`��֌W�̏������s���N���X�ł��B
 */

#pragma once

class CPlayer;

class CPlayerRenderer : public IGameObject {
public:
	CPlayerRenderer(CPlayer* pl) :
		m_player(pl)
	{
	}
	/*!
	 * @brief	�X�^�[�g�B
	 */
	void Awake() override;
	/*!
	 * @brief	�X�V�B
	 */
	void Update() override;
	/*!
	 * @brief	�`��
	 *@param[in]	rc		�����_�����O�R���e�L�X�g�B
	 */
	void Render(CRenderContext& rc) override;
	/*!
	* @brief	�X�L�����f���f�[�^�̎擾�B
	*/
	CSkinModelData& GetSkinModelData()
	{
		return m_skinModelData;
	}
	/*!
	* @brief	�X�L�����f���f�[�^�̎擾�B
	*/
	const CSkinModelData& GetSkinModelData() const
	{
		return m_skinModelData;
	}
	/*!
	 *@brief	�X�L�����f���̎擾�B
	 */
	CSkinModel& GetSkinModel()
	{
		return m_skinModel;
	}
private:
	CSkinModelData m_skinModelData;		//!<�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;				//!<�X�L�����f���B
	CShaderResourceView m_normalMap;	//!<�@���}�b�v�B
	CShaderResourceView m_specMap;		//!<�X�y�L�����}�b�v�B
	CShaderResourceView m_wnormalMap;	//!<����̖@���}�b�v�B
	CShaderResourceView m_wspecMap;		//!<����̃X�y�L�����}�b�v�B
	CPlayer* m_player = nullptr;		//!<�v���C���[�B	
};