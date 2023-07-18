#pragma once
#include <vector>

class SoundManager
{
public:
	enum class BgmId
	{
		Title,// �^�C�g��
		Main,// ���C��
		Result// ���U���g
	};

	SoundManager();
	virtual ~SoundManager();

	// ���[�h
	void Load();
	// �A�����[�h
	void Unload();

	// �Đ�
	void Start(int id, int volume);
	// �I��
	void Stop(int id);
	// ���[�v
	void Loop(int id);

private:
	

	std::vector<int> m_BgmHandle;// BGM�̃n���h��
};

