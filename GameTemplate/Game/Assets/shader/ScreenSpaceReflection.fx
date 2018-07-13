/*!
 * @brief	SSR
 */
#include "CommonFunc.h"

struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

//�J�����p�����[�^�̒萔�o�b�t�@
cbuffer cb : register(b0){
	float4x4 mViewProjInv;		//�r���[�v���W�F�N�V�����s��̋t�s��B
	float4x4 mViewProj;			//�r���[�v���W�F�N�V�����s��B
	float4 cameraPosInWorld;	//���[���h���W�n�ł̃J�����̎��_�B
};

Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`���B
Texture2D<float4> normalTexture : register(t1);	//�@���e�N�X�`���B
Texture2D<float4> depthTexture : register(t2);	//�[�x�e�N�X�`���B
Texture2D<float4> specTexture : register(t3);	//���؂����e�N�X�`���B

sampler Sampler : register(s0);


float GetRandomNumber(float2 texCoord, int Seed)
{
	return frac(sin(dot(texCoord.xy, float2(12.9898, 78.233)) + Seed) * 43758.5453);
}


PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	//�s�N�Z���̃��[���h���W���v�Z����B
	float3 worldPos = CalcWorldPosFromUVZ(
		In.uv,
		depthTexture.Sample(Sampler, In.uv).r,
		mViewProjInv
	);
	float4 sceneColor = sceneTexture.Sample(Sampler, In.uv);
	//�s�N�Z���̖@�����擾�B
	float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
	//�J�����̎��_����s�N�Z���Ɍ������x�N�g�����v�Z����B
	float3 toPixelDir = normalize( worldPos - cameraPosInWorld );
	//���˃x�N�g�������߂�B
	float3 toPixelDirReflect = reflect( toPixelDir, normal );
	//���˃x�N�g�����g���āA���C�}�[�`���O���s���B
	//���C�}�[�`���O�̃C�e���[�V�����񐔂Ɛ�����L�΂�������
	//��Œ萔�o�b�t�@�ɂ�����ŁH
	float spec = specTexture.Sample(Sampler, In.uv);
	for( int step = 0; step < 50; step++){
		worldPos += toPixelDirReflect * 2.0f * GetRandomNumber( In.uv, 1 );
		float4 posInProj = float4(worldPos, 1.0f);
		//�r���[�v���W�F�N�V������Ԃɕϊ�����B
		posInProj = mul(mViewProj, posInProj);
		posInProj.xyz /= posInProj.w;
		posInProj.xy = posInProj.xy * float2(0.5f, -0.5f) + 0.5f;
		float pixelZ = depthTexture.Sample(Sampler, posInProj.xy).r;
		if (posInProj.z - pixelZ > 0 && posInProj.z - pixelZ < 0.001f ) {
			//�Ԃ������̂Ń��C�}�[�`���O�I���B
			float4 reflectColor = sceneTexture.Sample(Sampler, posInProj.xy);
			float reflectRate = spec * 0.5f;
			sceneColor = lerp(sceneColor, reflectColor, reflectRate);
			break;
		}
	}
	return float4(sceneColor.xyz, 1.0f);//sceneTexture.Sample(Sampler, In.uv);
}