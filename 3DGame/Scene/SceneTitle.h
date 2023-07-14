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
	// �^�C�g�����S�̍X�V����
	void UpdateTitleLogo();

	// press any botton�̓_�ŏ���
	bool DrawInterval();

// �ϐ�
private:
	// �|�C���^
	std::shared_ptr<GameSetting> m_pSet;// ���ݒ�
	std::shared_ptr<Player> m_pPlayer;// �v���C���[
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// �G�l�~�[
	std::shared_ptr<EnemyBig> m_pEnemyBig;// �傫���G�l�~�[
	std::shared_ptr<Field> m_pField;// �X�e�[�W
	std::shared_ptr<BackDrop> m_pBackDrop;// �w�i

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

	// �_�ŕ`�悷�鎞�̎���
	int m_drawflashingInterval;

	// ���u�����h�̃p�����[�^
	int m_alphaParameter;

	// -------------------------
	// �e�X�g�ϐ�
	// -------------------------

	// -------------------------
	// ��������������g��Ȃ�
	// -------------------------
	// �ۉe���W
	int m_charPosX;// X
	int m_charPosY;// Y
	// �ۉe�傫��
	int m_charScaleX;// X
	int m_charScaleY;// Y
};

