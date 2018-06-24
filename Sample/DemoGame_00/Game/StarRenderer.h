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

	void UpdateWorldMatrix(const CVector3& trans,	const CQuaternion& rot,	const CVector3& scale );
	
private:
	prefab::CSkinModelRender* m_modelRender = nullptr;	//!<���f�������_���B
	int m_numStar = 0;
};

