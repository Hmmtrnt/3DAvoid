#pragma once
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class Enemy
{
public:
	// ���[�h���郂�f�����w�聨�w�肳�ꂽ���f�������[�h���Đ���
	Enemy(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// ���łɃ��[�h����Ă��郂�f���̃n���h�����w�聨Duplicate���Đ���
	Enemy(int orgModel, std::shared_ptr<Player> pPlayer);

	virtual ~Enemy();

	void Init();
	void End();
	void Update();
	void Draw();

	void UpdateMove();// �G�l�~�[�̓���

	void UpdateHit(int playerHp, bool hit);// �G�l�~�[�ƃv���C���[�����������Ƃ��̏���

	bool ColFlag();// �����蔻��̃e�X�g

	// ���f���̎擾
	int GetModelHandle()const;

	// �����蔻��̔��a
	float GetColRadius();

	// �G�l�~�[�̈ʒu�擾
	VECTOR GetPos()const { return m_pos; }

	// �����蔻��̐^�U�擾
	bool GetIsCol()const { return m_isCol; }

	// �����������̏���
	void SetPlayerPos(VECTOR playerPos);

	// �����o�֐��|�C���^
	void(Enemy::* m_updateFunc)();

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;// ���f��
	std::shared_ptr<Player> m_pPlayer;// �v���C���[

	// VECTOR
	VECTOR m_pos;		// �G�l�~�[���W
	VECTOR m_dir;		// �G�l�~�[�̕���
	VECTOR m_vec;		// �G�l�~�[�̈ړ�
	VECTOR m_playerPos;	// �v���C���[�̓����������̍��W
	VECTOR m_testPlayerVec = VGet(0.0f, 0.0f, 0.0f);// �v���C���[�̃x�N�g��

	// float
	float m_angle;		// �G�l�~�[�̃A���O��
	

	// int
	int m_modelHandle;	// �G�l�~�[�̃��f���n���h��
	int m_playerHandle;

	// bool
	bool m_isCol;// �G�l�~�[�̓����蔻��̐^�U

	// vector
	//std::vector<int> m_enemies;// �G�l�~�[�̐�

	MV1_COLL_RESULT_POLY_DIM test;
};

