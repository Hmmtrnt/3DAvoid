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

	// ���f���̎擾
	int GetModelHandle()const;

	// �����蔻��̔��a
	float GetColRadius();

	// �G�l�~�[�̈ʒu�擾
	VECTOR GetPos()const { return m_pos; }

	// �����o�֐��|�C���^
	void(Enemy::* m_updateFunc)();

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;// ���f��
	std::shared_ptr<Player> m_pPlayer;// �v���C���[

	// VECTOR
	VECTOR m_pos;		// �G�l�~�[���W

	// float
	float m_angle;		// �G�l�~�[�̃A���O��

	// int
	int m_modelHandle;	// �G�l�~�[�̃��f���n���h��

	// vector
	//std::vector<int> m_enemies;// �G�l�~�[�̐�
};

