#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>
#include <vector>

class GameSetting;
class Player;
class EnemyBase;
class Enemy;
class EnemyBig;
class Field;
class BackDrop;
class StringInit;
class Pause;
class SoundManager;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

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
	std::shared_ptr<BackDrop> m_pBackDrop;// �w�i
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// �G�l�~�[
	std::vector<std::shared_ptr<EnemyBig>> m_pEnemyBig;// �傫���G�l�~�[
	std::shared_ptr<StringInit> m_pFont;// �t�H���g
	std::shared_ptr<Pause> m_pPause;// �|�[�Y���
	std::shared_ptr<SoundManager> m_pSound;// ���y

	// int
	int m_shadowMap; // �V���h�E�}�b�v
	int m_invincibleTime;// �v���C���[�̖��G����
	int m_hpRedColor;// Hp�̃J���[��
	unsigned int m_hpColor;// Hp�̃J���[
	int m_score;// �Q�[���̃X�R�A
	int m_red;// �Ԃ̒l
	int m_decreaseColor;// �F�������Ă����ϐ�
	// �������邽�߂̃R�s�[
	int m_enemyModelHandle;// �G�l�~�[
	int m_shadowHandle;// �ۉe
	int m_fontHpHandle;// HP�̃t�H���g�n���h��
	int m_fontScoreHnadle;// �X�R�A�̃t�H���g�n���h��
	int m_scoreHandle;// �X�R�A�����₷������n���h��
	int m_selectNum;// �|�[�Y��ʂ̑I��ԍ�

	// bool
	bool m_hit;// �����������ǂ���
	bool m_hitting;// �������Ă���
	bool m_pushPause;// �|�[�Y�{�^�������������ǂ���
	bool m_isNoteOpen;// ���ӏ������J���Ă��邩�ǂ���

};
