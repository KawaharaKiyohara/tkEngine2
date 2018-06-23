/*!
 * @brief	�f�B�t�@�[�h�V�F�[�f�B���O�B
 */
#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"

#include "LightingFunction.h"

cbuffer PSDefferdCb : register( b0 )
{
	float4x4 mViewProjInv;	//�r���[�v���W�F�N�V�����s��̋t�s��B
};

struct VSDefferdInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSDefferdInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

PSDefferdInput VSMain( VSDefferdInput In ) 
{
	PSDefferdInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

/*!
 * @brief	UV���W���烏�[���h���W���v�Z����B
 */
float3 CalcWorldPosFromUV( float2 uv )
{
	float3 screenPos;
	screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2( -1.0f, 1.0f);
	screenPos.z = depthMap.Sample(Sampler, uv).r;
	
	float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
	worldPos.xyz /= worldPos.w;
	return worldPos.xyz;
}
float4 PSMain( PSDefferdInput In ) : SV_Target0
{
	//�A���x�h�B
	float4 albedo = albedoTexture.Sample(Sampler, In.uv);

	//�ڃx�N�g�����擾�B�B
	float3 tangent = tangentMap.Sample(Sampler, In.uv);
	//�ڃx�N�g����Ԃ̖@�����擾�B
	float3 normal = normalMap.Sample(Sampler, In.uv);
	//�]�@�����v�Z�B(todo ��Ŏ����H	)
	float3 biNormal = normalize(cross(tangent, normal));

	//���[���h���W���v�Z����B
	float3 worldPos = CalcWorldPosFromUV( In.uv );

	float3 lig = 0.0f;
	//���_�܂ł̃x�N�g�������߂�B
	float3 toEye = normalize(eyePos - worldPos);

	//�X�y�L�����B
	float specPow = 0.0f;
	float roughness = 1.0f;
	float4 t = specularMap.Sample(Sampler, In.uv);
	specPow = t.x;
	roughness = 1.0f - t.y;
	roughness *= 0.8f;	//@todo �}�e���A���p�����[�^�ɂ��ׂ����ȁB
	
	float toEyeLen = length(toEye);
	float3 toEyeDir = float3(1.0f, 0.0f, 0.0f);
	if (toEyeLen > 0.001f) {
		toEyeDir = toEye / toEyeLen;
	}

	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;

	//�e�}�b�v���Q��
	float shadow = softShadowMap.Sample(Sampler, In.uv).r;
	//�f�B���N�V�������C�g
	float3 finalColor = 0.0f;

	if (shadow < 0.99f) {
		//�e��������\�����Ⴂ�ꍇ�̂݌v�Z����B
		finalColor = CalcDirectionLight(
			albedo,
			worldPos,
			normal,
			tangent,
			biNormal,
			toEyeDir,
			toEyeReflection,
			roughness,
			specPow
		) * (1.0f - shadow);
	}

	//�|�C���g���C�g���v�Z�B
	finalColor += CalcPointLightInner(
		albedo,
		worldPos,
		In.uv,
		normal,
		tangent,
		biNormal,
		toEyeDir,
		toEyeReflection,
		roughness,
		specPow
	);

	//�A���r�G���g���C�g�B
	finalColor += CalcAmbientLight(
		albedo,
		normal,
		tangent,
		biNormal,
		toEyeDir,
		roughness,
		specPow
	);

	// brightness
	float brightness = 1.0f;
	finalColor *= brightness;
	/*
	// exposure
	float exposure = 1.0f;
	finalColor *= pow( 2.0, exposure );
	*/
	float gamma = 2.2f;
	finalColor = max(0.0f, pow(finalColor, 1.0 / gamma));
	if (isnan(finalColor.x) || isnan(finalColor.y) || isnan(finalColor.z)) {
		return float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	return float4(finalColor, 1.0f);
}
