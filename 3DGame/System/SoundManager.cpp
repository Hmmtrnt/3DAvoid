#include "SoundManager.h"
#include "DxLib.h"
#include <vector>

namespace
{
	// BGMハンドル
	std::vector<int> kHandle;

	const char* const kFileName[Sound::BgmNum] =
	{
		"Data/Sound/BGM/Title.mp3",
		"Data/Sound/BGM/Main.mp3",
		"Data/Sound/BGM/Result.mp3"
	};
}

namespace Sound
{
	void Load()
	{
		// データ読み込み
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			kHandle.push_back(handle);
		}
	}
	void Unload()
	{
		// データ解放
		for (auto& handle : kHandle)
		{
			DeleteSoundMem(handle);
		}
	}
	void Start(BgmId id, int volume)
	{
		int test = id;
		PlaySoundMem(kHandle[id], DX_PLAYTYPE_LOOP, true);
		ChangeVolumeSoundMem(volume, kHandle[id]);
	}
	void Stop(BgmId id)
	{
		StopSoundMem(kHandle[id]);
	}
}

//SoundManager::SoundManager()
//{
//	for (auto& handle : m_BgmHandle)
//	{
//		handle = -1;
//	}
//}
//
//SoundManager::~SoundManager()
//{
//}
//
//// ロード
//void SoundManager::Load()
//{
//	// データ読み込み
//	for (auto& fileName : kFileName)
//	{
//		int handle = LoadSoundMem(fileName);
//		m_BgmHandle.push_back(handle);
//	}
//}
//
//// アンロード
//void SoundManager::Unload()
//{
//	// データ解放
//	for (auto& handle : m_BgmHandle)
//	{
//		DeleteSoundMem(handle);
//	}
//}
//
//// 再生
//void SoundManager::Start(int id, int volume)
//{
//	//int test = id;
//	PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_LOOP, true);
//	ChangeVolumeSoundMem(volume, m_BgmHandle[id]);
//}
//
//// 終了
//void SoundManager::Stop(int id)
//{
//	StopSoundMem(m_BgmHandle[id]);
//}
//
//// ループ
//void SoundManager::Loop(int id)
//{
//	if (CheckSoundMem(m_BgmHandle[id]) != 1)
//	{
//		PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_BACK, true);
//	}
//}
