// �V�[�����U���g
#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>

class GameSetting;
class StringInit;
class BackDrop;
class Player;
class Scaffold;
class SoundManager;

class SceneResult : public SceneBase
{
public:
	SceneResult(int score);
	virtual ~SceneResult();

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
	std::shared_ptr<GameSetting> m_pSet;// �Q�[���̐ݒ�
	std::shared_ptr<StringInit> m_pFont;// �t�H���g
	std::shared_ptr<BackDrop> m_pBackDrop;// �w�i
	std::shared_ptr<Player> m_pPlayer;// �v���C���[
	std::shared_ptr<Scaffold> m_pScaffold;// ����
	std::shared_ptr<SoundManager> m_pSound;// ���y

	// int
	int m_score;// �Q�[���œ����X�R�A
	int m_scoreWriting;// �����_�̃X�R�A����������
	int m_highScore;// �t�@�C���̒��ɂ���n�C�X�R�A
	int m_fontHpHandle;// �t�H���g�n���h��
	int m_resultHandle;// ���U���g��ʂ̌��ʕ\���̃n���h��
	int m_guideHandle[2];// ���̃V�[���̃K�C�h�n���h��

	bool m_oneMore;// ������x�v���C���邩�ǂ���

};

