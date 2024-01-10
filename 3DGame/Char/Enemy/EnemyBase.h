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

	void Init(){}	// ������
	void End(){}	// �I����
	void Update(){}	// �X�V����
	void Draw(){}	// �`��

	// �G�l�~�[�̓���
	void EnemyMove();

	// �ۉe�`��
	void RoundShadow(float y, float scale);

	// ���f���̎擾
	int GetModelHandle()const;// �G�l�~�[
	int GetShadowHandle()const;// �ۉe

	// �G�l�~�[�̈ʒu�擾
	VECTOR GetPos()const { return m_pos; }

protected:
	// VECTOR
	VECTOR m_pos;		// �G�l�~�[���W
	VECTOR m_dir;		// �G�l�~�[�̕���
	VECTOR m_vec;		// �G�l�~�[�̈ړ�
	VECTOR m_scale;		// �G�l�~�[�̑傫��
	VECTOR m_EnemyDir;	// �G�l�~�[�̌�������

	// float
	float m_angle;		// �G�l�~�[�̃A���O��
	float m_speed;		// �G�l�~�[�̃X�s�[�h

	// int
	int m_modelHandle;	// �G�l�~�[�̃��f���n���h��
	int m_animMove;		// �G�l�~�[�̃��[�V�����ԍ�
	int m_roundShadowHandle;// �ۉe�n���h��
};

