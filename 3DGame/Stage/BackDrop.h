#pragma once
#include <array>
// �w�i����

class BackDrop
{
public:
	BackDrop();
	virtual ~BackDrop();

	void Update();
	void Draw();

private:
	// �w�i�ʒu���
	struct sBackImg
	{
		int m_width;			// ��
		int m_height;			// ����
	};

	// �摜�̈ʒu���
	sBackImg m_first;	// �ꖇ��
	sBackImg m_second;	// �񖇖�

	// int
	// ���W
	int m_handlePosX;// X
	int m_handlePosY;// Y
	int m_handlePosX2;// X
	int m_handlePosY2;// Y
	int m_scrollPower;// �X�N���[�����鑬�x

	int m_handle;// �w�i�̃n���h���f�[�^
	//std::array<sBackImg, 2> m_backImg;

};

