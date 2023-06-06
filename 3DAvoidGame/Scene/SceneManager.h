// シーンマネージャー
#pragma once

class SceneBase;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager() {}

	void Init();		// 初期化
	void End();			// 終了
	void Update();		// 毎フレームの処理
	void Draw();		// 描画

private:
	// シーンベースポインタ
	SceneBase* m_pScene;
};