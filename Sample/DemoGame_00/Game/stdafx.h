/*!
 *@brief	�v���R���p�C���ς݃w�b�_�[�B
 */
#pragma once

#include "resource.h"

#include "tkEngine/tkEnginePreCompile.h"
using namespace tkEngine;

enum EnMaterialID {
	enMaterialID_Chara = 1,
	enMaterialID_Star,
};

enum EnGameObjectTags {
	enGameObject_Star = 1,
	enGameObject_Enemy = 1 << 1,
};