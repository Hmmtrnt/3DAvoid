#include "GameSetting.h"

// 3D関連の設定
void GameSetting::Init3D()
{
	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);
}

//カメラの設定
void GameSetting::InitScenePlayPosCamera()
{
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(VGet(0, 1700, -400), VGet(0.0f, 0.0f, -100.0f));
}

void GameSetting::InitSceneOriginPosCamera()
{
	// near,far
	SetCameraNearFar(5.0f, 2000.0f);
	// カメラの視野角を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -400), VGet(0.0f, 0.0f, 0.0f));
}
