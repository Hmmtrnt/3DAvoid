#pragma once
#include <vector>

class SoundManager
{
public:
	enum class BgmId
	{
		Title,// タイトル
		Main,// メイン
		Result// リザルト
	};

	SoundManager();
	virtual ~SoundManager();

	// ロード
	void Load();
	// アンロード
	void Unload();

	// 再生
	void Start(int id, int volume);
	// 終了
	void Stop(int id);
	// ループ
	void Loop(int id);

private:
	

	std::vector<int> m_BgmHandle;// BGMのハンドル
};

