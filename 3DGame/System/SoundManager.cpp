#include "SoundManager.h"
#include "DxLib.h"

namespace
{
	// BGM�̐�
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

// ���[�h
void SoundManager::Load()
{
	// �f�[�^�ǂݍ���
	for (auto& fileName : kFileName)
	{
		int handle = LoadSoundMem(fileName);
		m_BgmHandle.push_back(handle);
	}
}

// �A�����[�h
void SoundManager::Unload()
{
	// �f�[�^���
	for (auto& handle : m_BgmHandle)
	{
		DeleteSoundMem(handle);
	}
}

// �Đ�
void SoundManager::Start(int id, int volume)
{
	//int test = id;
	PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_LOOP, true);
	ChangeVolumeSoundMem(volume, m_BgmHandle[id]);
}

// �I��
void SoundManager::Stop(int id)
{
	StopSoundMem(m_BgmHandle[id]);
}

// ���[�v
void SoundManager::Loop(int id)
{
	if (CheckSoundMem(m_BgmHandle[id]) != 1)
	{
		PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_BACK, true);
	}
}
