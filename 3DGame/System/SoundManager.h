#pragma once

// サウンド関連
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		Title,// タイトル
		Main,// メイン
		Result,// リザルト

		SoundNum
	}SoundId;

	// ロード、アンロード
	void Load();
	void UnLoad();

	// BGM再生
	void Start(SoundId id, int volume);

	void Stop(SoundId id);
	void Loop(SoundId id);

	void Play(SoundId id);

	void SetVolume(SoundId id, int volume);
}