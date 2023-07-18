#include "SoundManager.h"
#include "DxLib.h"

namespace
{
	// BGMの数
	constexpr int kBgmIdNum = 3;

	const char* const kFileName[kBgmIdNum] =
	{
		"Data/Sound/BGM/Title.mp3",
		"Data/Sound/BGM/Main.mp3",
		"Data/Sound/BGM/Result.mp3"
	};
}

SoundManager::SoundManager()
{
	for (auto& handle : m_BgmHandle)
	{
		handle = -1;
	}
}

SoundManager::~SoundManager()
{
}

// ロード
void SoundManager::Load()
{
	// データ読み込み
	for (auto& fileName : kFileName)
	{
		int handle = LoadSoundMem(fileName);
		m_BgmHandle.push_back(handle);
	}
}

// アンロード
void SoundManager::Unload()
{
	// データ解放
	for (auto& handle : m_BgmHandle)
	{
		DeleteSoundMem(handle);
	}
}

// 再生
void SoundManager::Start(int id, int volume)
{
	//int test = id;
	PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_LOOP, true);
	ChangeVolumeSoundMem(volume, m_BgmHandle[id]);
}

// 終了
void SoundManager::Stop(int id)
{
	StopSoundMem(m_BgmHandle[id]);
}

// ループ
void SoundManager::Loop(int id)
{
	if (CheckSoundMem(m_BgmHandle[id]) != 1)
	{
		PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_BACK, true);
	}
}
