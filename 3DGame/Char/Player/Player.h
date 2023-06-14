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

	
private:// �֐�
	void UpdatePlayerPos();// �L�����N�^�[����
	void UpdateCamera();// �J�����̍X�V����
	void UpdateVec();// �L�����N�^�[�̉����x
	void UpdateIdle();// �L�����N�^�[�̃A�C�h�����

	//--------------------------------------------------------
	// �e�X�g�֐�
	//--------------------------------------------------------
	void TestMove();// �L�����N�^�[�̓���+��


	// �����o�֐��|�C���^
	void (Player::* m_updateFunc)();
	
private:// �ϐ�
	// �|�C���^
	std::shared_ptr<Model> m_pModel;

	// VECTOR
	VECTOR m_playerPos;		// �v���C���[���W
	VECTOR m_playerAngle;	// �v���C���[�A���O��
	VECTOR m_playerVec;		// �v���C���[�̈ړ�
	VECTOR m_playerMove;	// �v���C���[�̓���

	// MATRIX
	MATRIX m_cameraRotMtx;	// �����ړ��̍s��擾
	MATRIX m_playerRotMtx;	// �v���C���[�̐i�s����

	// int
	int m_playerHandle;		// �L�����N�^�[�n���h��
	int m_AnimNum;			// �A�j���[�V�����̔ԍ�

	// float
	float m_playerAngle2;	// �v���C���[�A���O��
	float m_playerAngleY;	// �v���C���[��Y����]
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

	// �e�X�g
	int m_frameCount;

	int m_animPrev;//�O
	int m_animNext;//���

	
};

