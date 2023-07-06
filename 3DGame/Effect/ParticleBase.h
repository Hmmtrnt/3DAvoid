#pragma once
// �p�[�e�B�N���x�[�X
#include "../Util/common.h"

class ParticleBase
{
public:
	ParticleBase();
	virtual ~ParticleBase();

	void Init();
	void Update();
	void Draw();

	// �p�[�e�B�N���J�n
	void Start(VECTOR pos);

	// �ݒ�\�ȍ���
	void SetPos(VECTOR pos) { m_pos = pos; }// ���W
	void SetVec(VECTOR vec) { m_vec = vec; }// �ړ�
	void SetRadius(float radius) { m_radius = radius; }// ���̔��a

protected:
	// VECTOR
	VECTOR m_pos;// ���W
	VECTOR m_vec;// �ړ�

	// int
	int m_divNum;// �����`������|���S���ׂ̍���
	unsigned int m_difColor;// ���̒��_�f�B�t���[�Y�J���[
	unsigned int SpcColor;// ���̒��_�X�y�L�����[�J���[

	// float
	float m_radius;// ���̔��a

	// bool
	bool m_isExist;// ���݂��Ă��邩�ǂ���

};

