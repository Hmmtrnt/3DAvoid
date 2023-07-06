#pragma once
// �ł����G�l�~�[�̏���
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class EnemyBig
{
public:
	// ���[�h���郂�f�����w�聨�w�肳�ꂽ���f�������[�h���Đ���
	EnemyBig(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// ���łɃ��[�h����Ă��郂�f���̃n���h�����w�聨Duplicate���Đ���
	EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer, int num);

	virtual ~EnemyBig();

	void Init();
	void End();
	void Update();
	void Draw();

	void UpdateMove();// �G�l�~�[�̓���

	void DebugDraw();// �f�o�b�O�p�`��

	bool ColFlag();// �����蔻��̃e�X�g

	// ���f���̎擾
	int GetModelHandle()const;

	// �����蔻��̔��a
	float GetColRadius();

	// �G�l�~�[�̈ʒu�擾
	VECTOR GetPos()const { return m_pos; }

	// �����������̏���
	void SetPlayerPos(VECTOR playerPos);

	// �����o�֐��|�C���^
	void(EnemyBig::* m_updateFunc)();

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;// ���f��
	std::shared_ptr<Player> m_pPlayer;// �v���C���[

	// VECTOR
	VECTOR m_pos;		// �G�l�~�[���W
	VECTOR m_dir;		// �G�l�~�[�̕���
	VECTOR m_vec;		// �G�l�~�[�̈ړ�

	// float
	float m_angle;		// �G�l�~�[�̃A���O��
	float m_speed;		// �G�l�~�[�̃X�s�[�h

	// int
	int m_modelHandle;	// �G�l�~�[�̃��f���n���h��
	int m_Number;
};

