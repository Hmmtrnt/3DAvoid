// �t�H���g�f�[�^�ǂݍ���(�t�H���g�͑n�p�p�|�b�v�̂ɌŒ�)
#pragma once

class StringInit
{
public:
	StringInit();// �R���X�g���N�^
	virtual ~StringInit();// �f�X�g���N�^

	/// <summary>
	/// �t�H���g�f�[�^�쐬
	/// </summary>
	/// <param name="fontHandle">�摜�̃p�X</param>
	/// <param name="fontSize">�T�C�Y</param>
	/// <param name="fontThick">����</param>
	/// <param name="fontType">�^�C�v</param>
	void Init(int& fontHandle, int fontSize, int fontThick, int fontType);

	/// <summary>
	/// �t�H���g�f�[�^�폜
	/// </summary>
	/// <param name="fontHandle">�摜�̃p�X</param>
	void End(int& fontHandle);
};