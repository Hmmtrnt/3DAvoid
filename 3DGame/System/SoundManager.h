#pragma once
#include <vector>

// �T�E���h�֘A
namespace Sound
{
	enum SoundId
	{
		// BGM
		Title,// �^�C�g��
		Main,// ���C��
		Result,// ���U���g

		// SE
		TitleClick,// �^�C�g����ʂŃ{�^�����͎�
		Jump,// �W�����v������
		// �G�ɓ���������
		LowHit,// �̗͂��Ⴂ�Ƃ�
		MediumHit,// �̗͂����������Ƃ�
		StrongHit,// �̗͂������Ƃ�

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

	// ���y�Đ�
	void Start(Sound::SoundId id, int playType, int volume);
	void Loop(Sound::SoundId id);
	// ���y��~
	void Stop(Sound::SoundId id);
	// ���ʐݒ�
	void SetVolume(int volume, Sound::SoundId id);

private:
	std::vector<int> m_Handle;

};