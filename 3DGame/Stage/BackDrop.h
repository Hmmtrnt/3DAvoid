// �w�i����
#pragma once
#include <array>

class BackDrop
{
public:
	BackDrop();
	virtual ~BackDrop();

	void Update();
	void Draw();

	void MoveImage();	// �摜�̈ړ�

private:
	// �w�i�ʒu���
	struct sBackImg
	{
		int m_width;	// ��
		int m_height;	// ����
	};

	// �w�i�摜�̈ʒu���
	sBackImg m_first;	// �ꖇ��
	sBackImg m_second;	// �񖇖�

	int m_scrollSpeed;	// �X�N���[�����鑬�x
	int m_handle;// �w�i�̃n���h���f�[�^
};

