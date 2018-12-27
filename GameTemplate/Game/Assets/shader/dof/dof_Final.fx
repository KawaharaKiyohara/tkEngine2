/*!
 *@brief	Dof(��ʊE�[�x)
 *@details
 * �ŏI�����B
 */

Texture2D<float4> cocTexture : register(t0);	//CoC���������܂ꂽ�e�N�X�`��
Texture2D<float4> dofMasTexture : register(t1);	//��ʊE�[�x�̃}�X�N�e�N�X�`��
Texture2D<float4> bokeTexture_0 : register(t2);	//�{�P�e�N�X�`���@���x���O�B
Texture2D<float4> bokeTexture_1 : register(t3);	//�{�P�e�N�X�`���@���x���P�B

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

	//�s�N�Z����CoC���擾�B
	float coc = cocTexture.Sample( bilinearSampler, psIn.uv).a;
	coc = min( 1.0f, coc );
	//�����~�̔��a��0.001�ȉ��̓{�P�Ȃ��̂ŁA�s�N�Z���L���B
	clip( coc - 0.0001f );
	float4 colorTbl[3] = {
		cocTexture.Sample(bilinearSampler, psIn.uv),
		bokeTexture_0.Sample(bilinearSampler, psIn.uv),
		bokeTexture_1.Sample(bilinearSampler, psIn.uv),
	};
	
	float fTexIndex = min( 0.998f, coc ) / 0.5f;
	int iTexIndex = floor(fTexIndex);
	float blendRate = frac(fTexIndex);
	
	float4 blendColor = lerp(colorTbl[iTexIndex], colorTbl[iTexIndex+1], blendRate);
	//�K���Ƀ{�P�{�P
	return float4(blendColor.xyz, 1.0f);
}
