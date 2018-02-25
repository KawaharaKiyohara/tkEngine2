#pragma once
class PlayerSilhouette : public IGameObject
{
public:
	PlayerSilhouette();
	~PlayerSilhouette();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
private:
	CSkinModel* m_playerModel = nullptr;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	CShader m_psShader;	//�V���G�b�g�`��Ŏg�p����s�N�Z���V�F�[�_�[�B
	CShaderResourceView m_texture;	//�V���G�b�g�ŕ\������e�N�X�`��
};

