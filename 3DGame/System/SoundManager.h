#pragma once
#include <vector>

// サウンド関連
namespace Sound
{
	enum SoundId
	{
		// BGM
		Title,// タイトル
		Main,// メイン
		Result,// リザルト

		// SE
		TitleClick,// タイトル画面でボタン入力時
		Jump,// ジャンプした時
		// 敵に当たった時
		LowHit,// 体力が低いとき
		MediumHit,// 体力が少し多いとき
		StrongHit,// 体力が多いとき

		SoundNum
	};
}

class SoundManager
{
public:
	SoundManager();
	virtual ~SoundManager();

	void Load();
	void UnLoad();

	// 音楽再生
	void Start(Sound::SoundId id, int playType, int volume);
	void Loop(Sound::SoundId id);
	// 音楽停止
	void Stop(Sound::SoundId id);
	// 音量設定
	void SetVolume(int volume, Sound::SoundId id);

private:
	std::vector<int> m_Handle;

};