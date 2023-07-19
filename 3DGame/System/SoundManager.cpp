#include "SoundManager.h"
#include "DxLib.h"
#include <vector>

namespace
{
	// BGM�n���h��
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
		// �f�[�^�ǂݍ���
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			kHandle.push_back(handle);
		}
	}
	void Unload()
	{
		// �f�[�^���
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
//// ���[�h
//void SoundManager::Load()
//{
//	// �f�[�^�ǂݍ���
//	for (auto& fileName : kFileName)
//	{
//		int handle = LoadSoundMem(fileName);
//		m_BgmHandle.push_back(handle);
//	}
//}
//
//// �A�����[�h
//void SoundManager::Unload()
//{
//	// �f�[�^���
//	for (auto& handle : m_BgmHandle)
//	{
//		DeleteSoundMem(handle);
//	}
//}
//
//// �Đ�
//void SoundManager::Start(int id, int volume)
//{
//	//int test = id;
//	PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_LOOP, true);
//	ChangeVolumeSoundMem(volume, m_BgmHandle[id]);
//}
//
//// �I��
//void SoundManager::Stop(int id)
//{
//	StopSoundMem(m_BgmHandle[id]);
//}
//
//// ���[�v
//void SoundManager::Loop(int id)
//{
//	if (CheckSoundMem(m_BgmHandle[id]) != 1)
//	{
//		PlaySoundMem(m_BgmHandle[id], DX_PLAYTYPE_BACK, true);
//	}
//}
