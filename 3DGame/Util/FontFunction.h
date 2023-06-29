#pragma once
// �t�H���g�f�[�^�����t��������̕`��֐�(�t�H���g�͑n�p�p�|�b�v�̂ɌŒ�)

class FontFunction
{
public:
	FontFunction();// �R���X�g���N�^
	virtual ~FontFunction();// �f�X�g���N�^

	/// <summary>
	/// �t�H���g�f�[�^�쐬
	/// </summary>
	/// <param name="fontSize">�T�C�Y</param>
	/// <param name="fontThick">����</param>
	/// <param name="fontType">�^�C�v</param>
	void Init(int fontSize, int fontThick, int fontType);
	// �t�H���g�f�[�^�폜
	void End();
	/// <summary>
	/// �t�H���g�����t��������`��
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <param name="color">�J���[</param>
	/// <param name="string">������</param>
	/// <param name="num">�ϐ�������</param>
	void DrawFormat(int x, int y, unsigned int color, const char* string, int num);
	/// <summary>
	/// �t�H���g��������������`��
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <param name="string">������</param>
	/// <param name="color">�J���[</param>
	void DrawNoFormat(int x, int y, const char* string, unsigned int color);

private:
	int m_fontHandle;// �t�H���g�n���h��
};

