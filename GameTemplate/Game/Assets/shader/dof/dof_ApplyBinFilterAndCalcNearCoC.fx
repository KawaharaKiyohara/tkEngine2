/*!
 *@brief	Dof(��ʊE�[�x)
 *@details
 * �V�[���e�N�X�`���Ƀo�C���j�A�t�B���^�������āA
 * �J�����ɋ߂�����CoC(�����~�̔��a)�̌v�Z���s���܂��B
 * tkDof.cpp��ApplyBilinearFilterAndCalcNearCoc�֐��Ŏg���Ă���V�F�[�_�[�ł��B
 *
 * �Q�l���� Gpu gems3
 * ���LURL���Q��
 * https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch28.html
 */


/*!
 *@brief	�s�N�Z���V�F�[�_�[�ւ̓��́B
 */
struct PSIn{
	float4 position : SV_Position;
	float2 tcColor0 : TEXCOORD0;
	float2 tcColor1 : TEXCOORD1;
	float2 tcDepth0 : TEXCOORD2;
	float2 tcDepth1 : TEXCOORD3;
	float2 tcDepth2 : TEXCOORD4;
	float2 tcDepth3 : TEXCOORD5;
};

/*!
 *@brief	���_�V�F�[�_�[�B
 */
PSIn VSMain( float4 pos : POSITION, float2 tc : TEXCOORD0 )
{
	PSIn psIn = (PSIn)0;
	
	return psIn;
}
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( PSIn psIn ) : SV_Target0
{
	return float4( 0.0f, 0.0f, 0.0f, 1.0f);
}