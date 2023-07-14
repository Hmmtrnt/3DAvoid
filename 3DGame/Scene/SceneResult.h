#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>

class StringInit;
class BackDrop;

class SceneResult : public SceneBase
{
public:
	SceneResult(int score);// �R���X�g���N�^
	virtual ~SceneResult();// �f�X�g���N�^

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

// �֐�
private:
	// �t�@�C���̐�����������
	void GenerationFile();

	// �t�@�C���̏�������
	void ReadFile();
// �ϐ�
private:
	// �|�C���^
	std::shared_ptr<StringInit> m_pFont;
	std::shared_ptr<BackDrop> m_pBackDrop;

	// int
	int m_score;// �Q�[���œ����X�R�A
	int m_scoreWriting;// �����_�̃X�R�A����������
	int m_highScore;// �t�@�C���̒��ɂ���n�C�X�R�A
	int m_fontHandle;// �t�H���g�n���h��
};

