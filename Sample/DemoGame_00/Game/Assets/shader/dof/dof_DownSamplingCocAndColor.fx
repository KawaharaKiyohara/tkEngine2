/*!
 *@brief	Dof(��ʊE�[�x)
 *@details
 * �V�[���摜��CoC�f�[�^�̃_�E���T���v�����O
 */

Texture2D<float4> sceneAndCocTexture : register(t0);	//�V�[���e�N�X�`���B
sampler pointSampler : register(s0);			//�|�C���g�T���v�����O���s���T���v���B
sampler linearSampler : register(s1);			//�o�C���j�A�T���v�����O���s���T���v���B

/*!
 *@brief	�s�N�Z���V�F�[�_�[�ւ̓��́B
 */
struct PSIn{
	float4 position : SV_Position;
	float2 uv0		: TEXCOORD0;
	float2 uv1		: TEXCOORD1;
	float2 uv2		: TEXCOORD2;
	float2 uv3		: TEXCOORD3;
};

/*!
 *@brief	�萔�o�b�t�@�B
 * ���̒��g��ύX������AtkDof.h��SDownSamplingCocAndColorCB��
 * �X�V����B
 */
cbuffer cbParam : register( b0 )
{
	float2 invRenderTargetSize;		//�����_�����O�^�[�Q�b�g�̋t���B
};
/*!
 *@brief	���_�V�F�[�_�[�B
 */
PSIn VSMain( float4 pos : POSITION, float2 uv : TEXCOORD0 )
{
	PSIn psIn = (PSIn)0;
	psIn.position = pos;
	psIn.uv0 = uv + float2( -1.0f * invRenderTargetSize.x, 0.0f );
	psIn.uv1 = uv + float2(  1.0f * invRenderTargetSize.x, 0.0f );
	psIn.uv2 = uv + float2(                          0.0f,  1.0f * invRenderTargetSize.y );
	psIn.uv3 = uv + float2(                          0.0f, -1.0f * invRenderTargetSize.y );
	return psIn;
}
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( PSIn psIn ) : SV_Target0
{
	float4 color = sceneAndCocTexture.Sample( pointSampler, psIn.uv0 );
	color += sceneAndCocTexture.Sample( pointSampler, psIn.uv1 );
	color += sceneAndCocTexture.Sample( pointSampler, psIn.uv2 );
	color += sceneAndCocTexture.Sample( pointSampler, psIn.uv3 );
	color /= 4.0f;
	return color;
}
