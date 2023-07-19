#pragma once

namespace Sound
{
	enum BgmId
	{
		Title,// �^�C�g��
		Main,// ���C��
		Result,// ���U���g
		BgmNum// BGM�̐�
	};

	// ���[�h
	void Load();
	// �A�����[�h
	void Unload();

	// �Đ�
	void Start(BgmId id, int volume);
	// �I��
	void Stop(BgmId id);
}

//class SoundManager
//{
//public:
//	enum class BgmId
//	{
//		Title,// �^�C�g��
//		Main,// ���C��
//		Result,// ���U���g
//		BgmNum// BGM�̐�
//	};
//
//	SoundManager();
//	virtual ~SoundManager();
//
//	// ���[�h
//	void Load();
//	// �A�����[�h
//	void Unload();
//
//	// �Đ�
//	void Start(int id, int volume);
//	// �I��
//	void Stop(int id);
//	// ���[�v
//	void Loop(int id);
//
//private:
//	
//
//	std::vector<int> m_BgmHandle;// BGM�̃n���h��
//};



