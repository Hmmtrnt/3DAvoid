#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>
#include <vector>

class GameSetting;
class Player;
class Enemy;
class Field;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

	void UpdateEnemy();

// �֐�
private:
	// �_���[�W�\�L�ɂ���ĐF�ύX
	void UpdateColor();


// �ϐ�
private:
	// �Q�[���̐ݒ�|�C���^
	std::shared_ptr<GameSetting> m_pSet;// ���ݒ�
	std::shared_ptr<Player> m_pPlayer;// �v���C���[
	std::shared_ptr<Field> m_pField;// �X�e�[�W
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// �G�l�~�[

	// int
	int m_shadowMap; // �V���h�E�}�b�v
	int m_invincibleTime;// �v���C���[�̖��G����
	int m_hpRedColor;// Hp�̃J���[��
	unsigned int m_hpColor;// Hp�̃J���[
	int m_score;// �Q�[���̃X�R�A
	int m_BackGroundHandle;// �w�i�̃n���h��

	// �f�o�b�O�p�ϐ��G�̔ԍ�������
	int m_debugEnemyNum = 0;

	// bool
	bool m_hit;// �����������ǂ���
	bool m_hitting;// �������Ă���
};
