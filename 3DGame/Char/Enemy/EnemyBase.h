#pragma once
// �G�l�~�[�x�[�X
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	void Init(){}
	void End(){}
	void Update(){}
	void Draw(){}

protected:

	// VECTOR
	VECTOR m_pos;		// �G�l�~�[���W
	VECTOR m_dir;		// �G�l�~�[�̕���
	VECTOR m_vec;		// �G�l�~�[�̈ړ�

	// float
	float m_angle;		// �G�l�~�[�̃A���O��
	float m_speed;		// �G�l�~�[�̃X�s�[�h

	// int
	int m_modelHandle;	// �G�l�~�[�̃��f���n���h��
};

