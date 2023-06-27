#pragma once
#include "../../Util/common.h"
#include <memory>

class Model;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	void UpdateHit();

	// �v���C���[�̍��W�擾
	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }

	VECTOR m_pos;		// �v���C���[���W
	VECTOR m_vec;		// �v���C���[�̈ړ�

	// �v���C���[��HP�擾
	int GetBlowRate() { return m_blowRate; }

	bool GetIsFall()const { return m_isFall; }
	
private:// �֐�
	void UpdatePlayerPos();// �L�����N�^�[����
	void UpdateCamera();// �J�����̍X�V����
	void UpdateVec();// �L�����N�^�[�̉����x
	void UpdateIdle();// �L�����N�^�[�̃A�C�h�����

	//--------------------------------------------------------
	// �e�X�g�֐�
	//--------------------------------------------------------
	void TestMove();// �L�����N�^�[�̓���+��

	int TestCalculate();// �A���O���̌v�Z

	// �����o�֐��|�C���^
	void (Player::* m_updateFunc)();
	
private:// �ϐ�
	// �|�C���^
	std::shared_ptr<Model> m_pModel;

	// VECTOR
	
	VECTOR m_angle;		// �v���C���[�A���O��
	
	VECTOR m_move;		// �v���C���[�̓���

	// MATRIX
	MATRIX m_cameraRotMtx;	// �����ړ��̍s��擾
	MATRIX m_playerRotMtx;	// �v���C���[�̐i�s����

	// int
	int m_playerHandle;		// �L�����N�^�[�n���h��
	int m_AnimNum;			// �A�j���[�V�����̔ԍ�
	int m_blowRate;// ������ї�

	// float
	float m_playerAngle2;	// �v���C���[�A���O��
	float m_playerAngleY;	// �v���C���[��Y����]
	//float m_playerRotation;	// �v���C���[�̉�]
	float m_cameraAngle;	// �J�����A���O��

	float m_AnimTotalTime;	// �A�j���[�V�����̑S�̃t���[��
	float m_AnimPlay;		// �A�j���[�V�����̍Đ�

	float m_jumpAcc;		// �W�����v�����x


	// bool
	bool m_pressUp;			// ��L�[���������������ǂ���
	bool m_pressDown;		// ���L�[���������������ǂ���
	bool m_pressRight;		// �E�L�[���������������ǂ���
	bool m_pressLeft;		// ���L�[���������������ǂ���

	bool m_isJump;			// �W�����v���Ă��邩�ǂ���
	bool m_isMove;			// �����Ă��邩�ǂ���
	bool m_isFall;			// �X�e�[�W�O�ɏo�����ǂ���

	// �e�X�g
	int m_frameCount;

	int m_animPrev;//�O
	int m_animNext;//���

	

	float m_angleTest = 0.0f;// ��]�ő�l
	
	float m_testRusult = 0.0f;// �v�Z����

	bool m_isFlag = false;// ��]

	MV1_COLL_RESULT_POLY_DIM test;

};

