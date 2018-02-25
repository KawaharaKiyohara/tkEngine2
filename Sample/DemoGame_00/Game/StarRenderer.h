#pragma once
//���̕`��N���X�B
class StarRenderer : public IGameObject
{
public:
	StarRenderer();
	~StarRenderer();
	/*!
	 *@brief	�������B
	 *@param[in]	numStar		���̐��B
	 */
	void Init(int numStar)
	{
		m_numStar = numStar;
	}
	/*!
	 *@brief	�J�n���ɌĂ΂�鏈���B
	 */
	bool Start() override;
	/*!
	*@brief	�X�V
	*/
	void Update() override
	{
	}
	/*!
	 *@brief	���O�A�b�v�f�[�g�B
	 */
	void PreUpdate() override;
	
	/*!
	 *@brief	�x���X�V�B
	 */
	void PostUpdate() override;
	/*!
	*@brief	�`��
	*/
	void Render(CRenderContext& renderContext) override;
	void UpdateWorldMatrix(const CVector3& trans,	const CQuaternion& rot,	const CVector3& scale );
	
private:
	CSkinModelData	m_skinModelData;	//!<�X�L�����f���f�[�^�B
	CSkinModel		m_skinModel;		//!<�X�L�����f���B	
	int m_numStar = 0;
};

