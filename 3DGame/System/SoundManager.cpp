#include "SoundManager.h"
#include <vector>
#include "DxLib.h"

namespace
{
	// サウンドハンドル
	std::vector<int> kHandle;

	const char* const kFileName[Sound::SoundNum] =
	{
		"Data/Sound/BGM/Title.mp3",
		"Data/Sound/BGM/Main.mp3",
		"Data/Sound/BGM/Result.mp3",
	};
}

namespace Sound
{
	void Sound::Load()
	{
		// サウンドデータの読み込み
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			kHandle.push_back(handle);
		}
	}

	void Sound::UnLoad()
	{
		// サウンドデータの解放
		for (auto& handle : kHandle)
		{
			DeleteSoundMem(handle);
			handle = -1;
		}
	}

	void Sound::Start(SoundId id, int volume)
	{
		PlaySoundMem(kHandle[id], DX_PLAYTYPE_BACK, true);
		SetVolume(id, volume);
	}

	void Sound::Stop(SoundId id)
	{
		StopSoundMem(kHandle[id]);
	}

	void Sound::Loop(SoundId id)
	{
		if (CheckSoundMem(kHandle[id]) != 1)
		{
			PlaySoundMem(kHandle[id], DX_PLAYTYPE_BACK, true);
		}
	}

	void Sound::Play(SoundId id)
	{
		PlaySoundMem(kHandle[id], DX_PLAYTYPE_BACK, true);
	}

	void Sound::SetVolume(SoundId id, int volume)
	{
		ChangeVolumeSoundMem(volume, kHandle[id]);
	}
}

