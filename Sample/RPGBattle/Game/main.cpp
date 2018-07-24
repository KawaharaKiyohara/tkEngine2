/*!
 *@brief	main.cpp
 */
#include "stdafx.h"
#include "Game.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand((unsigned)time(NULL));
	//tkEngine2�̏������p�����[�^��ݒ肷��B
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
#if !defined(USE_LOW_SPEC_SETTINGS)
	initParam.screenWidth = 1920;
	initParam.screenHeight = 1080;
	initParam.frameBufferWidth = 1920;
	initParam.frameBufferHeight = 1080;
	initParam.screenWidth2D = 1280;
	initParam.screenHeight2D = 720;
	//�e�̐ݒ�B
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfing.shadowRenderConfig.lightHeight = UnitM(10.0f);
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[0] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[1] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[2] = 0.002f;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;

	//�A���`
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = true;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
	//SSR
	initParam.graphicsConfing.ssrConfig.isEnable = true;
	//�f�B�U
	initParam.graphicsConfing.ditheringConfig.isEnable = true;
#else
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 640;
	initParam.frameBufferHeight = 360;
	initParam.screenWidth2D = 1920;
	initParam.screenHeight2D = 1080;
	//�e�̐ݒ�B
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 512;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 512;
	initParam.graphicsConfing.shadowRenderConfig.lightHeight = UnitM(20.0f);
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[0] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[1] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[2] = 0.002f;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;

	//�A���`
	initParam.graphicsConfing.aaConfig.isEnable = false;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = true;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
	//SSR
	initParam.graphicsConfing.ssrConfig.isEnable = false;
	//�f�B�U
	initParam.graphicsConfing.ditheringConfig.isEnable = false;
#endif
	GraphicsEngine().GetShadowMap().SetFar(1000.0f);
	GraphicsEngine().GetShadowMap().SetNear(50.0f);

	//�G���W�����������B
	if (Engine().Init(initParam) == true) {
		NewGO<Game>(0, "Game");
		//�Q�[�����[�v�����s�B
		Engine().RunGameLoop();
	}
	//�G���W���̏I�������B
	Engine().Final();

	return 0;
}

