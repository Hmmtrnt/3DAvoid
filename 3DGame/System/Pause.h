#pragma once
// �|�[�Y����
// TODO:�f�o�b�O��ԂȂ̂Ō����ڂ��������肷��

class Pause
{
public:
	Pause();// �R���X�g���N�^
	virtual ~Pause();// �f�X�g���N�^

	void Update(int& selectNum);// �X�V����
	void DrawPause();// �|�[�Y�`�揈��

	void DrawNote();// ���ӏ����`��

private:
	// �e�X�g�ϐ�
	int m_posx = 200;// �J�[�\�����WX
	int m_posy = 200;// �J�[�\�����WY
	int m_selectNum = 0;// �J�[�\�����I�����Ă���ꏊ


};