#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>
#include <vector>

class GameSetting;
class Player;
class Enemy;
class Field;
class StringInit;
class Pause;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

	// DOTO:�֐����ύX
	void UpdateEnemy();// �G�ɓ����������̍X�V����

// �֐�
private:
	// �_���[�W�\�L�ɂ���ĐF�ύX
	void UpdateColor();

	// �|�[�Y�������Ă��Ȃ��Ƃ��̏���
	void UpdatePauseNo();
	// �|�[�Y���������Ƃ��̏���
	void UpdatePause();

	// �����o�֐��|�C���^
	void(SceneMain::* m_updateFunc)();

// �ϐ�
private:
	// �|�C���^
	std::shared_ptr<GameSetting> m_pSet;// ���ݒ�
	std::shared_ptr<Player> m_pPlayer;// �v���C���[
	std::shared_ptr<Field> m_pField;// �X�e�[�W
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// �G�l�~�[
	std::shared_ptr<StringInit> m_pFont;// �t�H���g
	std::shared_ptr<Pause> m_pPause;

	// int
	int m_shadowMap; // �V���h�E�}�b�v
	int m_invincibleTime;// �v���C���[�̖��G����
	int m_hpRedColor;// Hp�̃J���[��
	unsigned int m_hpColor;// Hp�̃J���[
	int m_score;// �Q�[���̃X�R�A
	int m_BackGroundHandle;// �w�i�̃n���h��

	int m_debugEnemyNum = 0;// �f�o�b�O�p�ϐ��G�̔ԍ�������

	int m_red;// �Ԃ̒l
	int m_decreaseColor;// �F�������Ă����ϐ�

	int m_enemyModelHandle;// �������邽�߂̓G�̃R�s�[

	int m_fontHandle;// �t�H���g�n���h��

	// bool
	bool m_hit;// �����������ǂ���
	bool m_hitting;// �������Ă���

	bool m_pushPause;// �|�[�Y�{�^�������������ǂ���
};
