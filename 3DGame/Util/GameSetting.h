// 3Dの設定
#pragma once
#include "DxLib.h"

class GameSetting
{
public:
	void Init3D();						// 3D関連の設定
	void InitScenePlayPosCamera();		// メインシーンのカメラの設定
	void InitSceneOriginPosCamera();	// タイトル画面のカメラ
};

