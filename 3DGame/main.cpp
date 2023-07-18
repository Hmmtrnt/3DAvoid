#include "DxLib.h"
#include "Util/game.h"
#include "Scene/SceneManager.h"
#include "Util/GameSetting.h"
#include <memory>

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowModo);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// ポインタ
	std::shared_ptr<SceneManager> pScene;// シーン
	pScene = std::make_shared<SceneManager>();
	std::shared_ptr<GameSetting> pSet;// ゲームの3D設定
	pSet = std::make_shared<GameSetting>();

	pSet->Init3D();// zバッファ有効
	
	pScene->Init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		pScene->Update();
		pScene->Draw();

		// 裏画面を表画面を入れ替える
		ScreenFlip();

		// escきーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	pScene->End();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}