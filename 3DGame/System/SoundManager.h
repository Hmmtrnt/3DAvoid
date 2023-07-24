#pragma once

// �T�E���h�֘A
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		Title,// �^�C�g��
		Main,// ���C��
		Result,// ���U���g

		SoundNum
	}SoundId;

	// ���[�h�A�A�����[�h
	void Load();
	void UnLoad();

	// BGM�Đ�
	void Start(SoundId id, int volume);

	void Stop(SoundId id);
	void Loop(SoundId id);

	void Play(SoundId id);

	void SetVolume(SoundId id, int volume);
}