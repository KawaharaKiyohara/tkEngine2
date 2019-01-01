/*!
 *@brief	Dof(��ʊE�[�x)
 *@details
 * �V�[���摜��CoC�f�[�^�̃_�E���T���v�����O
 */

Texture2D<float4> cocTexture : register(t0);	//�V�[���e�N�X�`���B
sampler linearSampler : register(s0);			//�o�C���j�A�T���v�����O���s���T���v���B

/*!
 *@brief	�s�N�Z���V�F�[�_�[�ւ̓��́B
 */
struct PSDownSampleIn{
	float4 position : SV_Position;
	float2 uv : TEXCOORD0;
};

/*!
 *@brief	�萔�o�b�t�@�B
 */
cbuffer cbDownSampleParam : register( b0 )
{
	float2 invRenderTargetSize;		//�����_�����O�^�[�Q�b�g�̋t���B
};
/*!
 *@brief	���_�V�F�[�_�[�B
 */
PSDownSampleIn VSDownSample( float4 pos : POSITION, float2 uv : TEXCOORD0 )
{
	PSDownSampleIn psIn = (PSDownSampleIn)0;
	psIn.position = pos;
	psIn.uv = uv + 0.5f * invRenderTargetSize;
	return psIn;
}
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSDownSample( PSDownSampleIn psIn ) : SV_Target0
{
	return cocTexture.Sample( linearSampler, psIn.uv );
}

