#include "SoundManager.h"
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
		"Data/Sound/SE/TitleClick.mp3",
		"Data/Sound/SE/Jump.mp3",
	};
}

SoundManager::SoundManager()
{
	for (auto& fileName : kFileName)
	{
		int handle = LoadSoundMem(fileName);
		m_Handle.push_back(handle);
	}

	/*m_Handle[0] = LoadSoundMem("Data/Sound/BGM/Title.mp3");
	m_Handle[1] = LoadSoundMem("Data/Sound/BGM/Main.mp3");
	m_Handle[2] = LoadSoundMem("Data/Sound/BGM/Result.mp3");*/
}

SoundManager::~SoundManager()
{
	for (int i = 0; i < 3; i++)
	{
		DeleteSoundMem(m_Handle[i]);
	}

	for (auto& handle : m_Handle)
	{
		DeleteSoundMem(handle);
	}
}

void SoundManager::Load()
{
	
}

void SoundManager::UnLoad()
{
	
}

void SoundManager::Start(Sound::SoundId id, int playType, int volume)
{
	ChangeVolumeSoundMem(volume, m_Handle[id]);
	PlaySoundMem(m_Handle[id], playType, true);
}

void SoundManager::Loop(Sound::SoundId id)
{
}

void SoundManager::Stop(Sound::SoundId id)
{
	StopSoundMem(m_Handle[id]);
}

void SoundManager::SetVolume(int volume, Sound::SoundId id)
{
	
}
