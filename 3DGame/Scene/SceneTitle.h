#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <vector>
#include <memory>

class GameSetting;
class Player;
class Enemy;
class EnemyBig;
class Field;
class BackDrop;
class SoundManager;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

// �֐�
private:
	// void
	// �^�C�g�����S�̍X�V����
	void UpdateTitleLogo();
	// �C���^�[�o����i�߂�
	void IntervalAdvance(int topNum);

	// bool
	// press any botton�̓_�ŏ���
	bool DrawInterval();
	// �{�^�����������Ƃ��̃C���^�[�o��
	bool DrawPushInterval();

// �ϐ�
private:
	// �|�C���^
	std::shared_ptr<GameSetting> m_pSet;// ���ݒ�
	std::shared_ptr<Player> m_pPlayer;// �v���C���[
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// �G�l�~�[
	std::shared_ptr<EnemyBig> m_pEnemyBig;// �傫���G�l�~�[
	std::shared_ptr<Field> m_pField;// �X�e�[�W
	std::shared_ptr<BackDrop> m_pBackDrop;// �w�i
	std::shared_ptr<SoundManager> m_pSound;// ��

	// int
	int m_titleHandle;// �^�C�g���̉摜�n���h��
	int m_stringHandle;// ������̉摜�n���h��
	int m_enemyHandle;// �G�l�~�[�n���h��
	int m_roundShadowHandle;// �ۉe�n���h��
	// �^�C�g�����W
	int m_titlePosX;// X
	int m_titlePosY;// Y
	// �^�C�g���傫��
	int m_titleScaleX;// ��
	int m_titleScaleY;// ����

	
	int m_drawFlashingInterval;// �_�ŕ`�悷�鎞�̎���
	int m_topNumInterval;// �_�ŕ`�悷��Ƃ��̎��Ԃ�����������^�C�~���O

	// ���u�����h�̃p�����[�^
	int m_alphaParameter;

	// bool
	bool m_isDraw;// �`�悳��邩�ǂ���
	bool m_isPush;// press any botton�������ꂽ���ǂ���

	// -------------------------
	// �e�X�g�ϐ�
	// -------------------------

	
};

