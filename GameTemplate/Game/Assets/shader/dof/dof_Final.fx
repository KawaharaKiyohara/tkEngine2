/*!
 *@brief	Dof(��ʊE�[�x)
 *@details
 * �ŏI�����B
 */

Texture2D<float4> cocTexture : register(t0);	//CoC���������܂ꂽ�e�N�X�`��
Texture2D<float4> dofMasTexture : register(t1);	//��ʊE�[�x�̃}�X�N�e�N�X�`��
Texture2D<float4> bokeTexture_0 : register(t2);	//�{�P�e�N�X�`���@���x���O�B


sampler pointSampler : register(s0);			//�|�C���g�T���v�����O���s���T���v���B
sampler bilinearSampler : register(s1);			//�o�C���j�A�T���v�����O���s���T���v���B

/*!
 *@brief	�s�N�Z���V�F�[�_�[�ւ̓��́B
 */
struct PSIn{
	float4 position : SV_Position;
	float2 uv		: TEXCOORD0;
};

/*!
 *@brief	���_�V�F�[�_�[�B
 */
PSIn VSMain( float4 pos : POSITION, float2 uv : TEXCOORD0 )
{
	PSIn psIn = (PSIn)0;
	psIn.position = pos;
	psIn.uv = uv;
	return psIn;
}
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( PSIn psIn ) : SV_Target0
{

	//��ʊE�[�x�������Ȃ��ӏ��̓s�N�Z���L���`
	float mask = dofMasTexture.Sample( bilinearSampler, psIn.uv );
	clip( mask - 0.1f );
	//�s�N�Z����CoC���擾�B
	float coc = cocTexture.Sample( bilinearSampler, psIn.uv).a;
	coc = min( 1.0f, coc ); 

	float4 blendColor = lerp(
		cocTexture.Sample(bilinearSampler, psIn.uv), 
		bokeTexture_0.Sample(bilinearSampler, psIn.uv), 
		coc
	);
	//�K���Ƀ{�P�{�P
	return float4(blendColor.xyz, 1.0f);
}
