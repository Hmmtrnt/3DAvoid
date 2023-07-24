#pragma once
// �|�[�Y����

class Pause
{
public:
	Pause();// �R���X�g���N�^
	virtual ~Pause();// �f�X�g���N�^

	void Update(int& selectNum);// �X�V����
	void DrawPause();// �|�[�Y�`�揈��
	void DrawNote();// ���ӏ����`��

	/// <summary>
	/// �|�[�Y��ʂ��J�������̏���
	/// </summary>
	/// <param name="isOpen">�|�[�Y��ʂ��J�������ǂ���</param>
	void UpdateOpen(bool isOpen);

private:
	// �e�X�g�ϐ�
	int m_posx;// �J�[�\�����WX
	int m_posy;// �J�[�\�����WY
	int m_selectNum;// �J�[�\�����I�����Ă���ꏊ

	// �I�����̍��W
	int m_selectPosX;
	int m_selectPosY;

	// �|�[�Y��ʂ̃n���h��
	int m_pauseHandle[4];

};