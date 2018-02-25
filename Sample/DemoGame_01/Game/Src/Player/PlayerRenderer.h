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
	~CPlayerRenderer();
	/*!
	 * @brief	�X�^�[�g�B
	 */
	void Awake() override;
	/*!
	 * @brief	�X�V�B
	 */
	void Update() override;
	/*!
	* @brief	�X�L�����f���f�[�^�̎擾�B
	*/
	CSkinModelData& GetSkinModelData()
	{
		return m_skinModelRender->GetSkinModelData();
	}
	/*!
	* @brief	�X�L�����f���f�[�^�̎擾�B
	*/
	const CSkinModelData& GetSkinModelData() const
	{
		return m_skinModelRender->GetSkinModelData();
	}
	/*!
	* @brief	�X�L�����f�������_���̎擾�B
	*/
	prefab::CSkinModelRender* GetSkinModelRender()
	{
		return m_skinModelRender;
	}
private:
	/*CSkinModelData m_skinModelData;		//!<�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;				//!<�X�L�����f���B*/
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CShaderResourceView m_normalMap;	//!<�@���}�b�v�B
	CShaderResourceView m_specMap;		//!<�X�y�L�����}�b�v�B
	CShaderResourceView m_wnormalMap;	//!<����̖@���}�b�v�B
	CShaderResourceView m_wspecMap;		//!<����̃X�y�L�����}�b�v�B
	CPlayer* m_player = nullptr;		//!<�v���C���[�B	
};