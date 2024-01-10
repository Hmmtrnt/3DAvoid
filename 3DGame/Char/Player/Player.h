// �v���C���[
#pragma once
#include "../../Util/common.h"
#include <memory>

class Model;
class Enemy;
class SoundManager;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();// ������
	void End();// �I��
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="Hitting">�������Ă���</param>
	void Update(bool Hitting);
	void Draw();// �`��
	
	void UpdateHitDamage(VECTOR enemyPos, bool hit);// �_���[�W
	void UpdateHitVec();// �G�l�~�[�ƃv���C���[�����������Ƃ��̏���
	void RoundShadow();// �v���C���[�̊ۉe

	void UpdateTitle();// �^�C�g����ʂ̃v���C���[�̍X�V����
	void UpdateResult();// ���U���g��ʂ̃v���C���[�̍X�V����

	void DrawUI(int color, int fontHandle);// �v���C���[��UI��`��

	// �v���C���[�̍��W�擾
	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }

	// �v���C���[��HP�擾
	int GetBlowRate()const { return m_blowRate; }

	// �����Ă��邩�ǂ����̐^�U
	bool GetIsFall()const { return m_isFall; }
	
// �֐�
private:
	void UpdateNoHitVec(bool Hitting);// �ړ�����
	void UpdateMotion(bool hit);
	void UpdateMove(bool Hitting);// �L�����N�^�[�̓���
	void PadInputState();// �p�b�h�̓��͏�Ԏ擾

	/// <summary>
	/// ���W�A��]�A�傫���ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�傫��</param>
	void InitState(VECTOR pos, VECTOR rot, VECTOR scale);
	
// �ϐ�
private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<SoundManager> m_pSound;// ���y

	// VECTOR
	VECTOR m_pos;		// �v���C���[���W
	VECTOR m_vec;		// �v���C���[�̈ړ�
	VECTOR m_hitVec;	// �����������̃v���C���[�̈ړ�
	VECTOR m_angle;		// �v���C���[�A���O��
	VECTOR m_move;		// �v���C���[�̓���
	VECTOR m_scale;		// �傫��

	// MATRIX
	MATRIX m_cameraRotMtx;	// �����ړ��̍s��擾
	MATRIX m_playerRotMtx;	// �v���C���[�̐i�s�����̍s��

	// int
	int m_playerHandle;		// �L�����N�^�[�n���h��
	int m_roundShadowHandle;// �L�����N�^�[�̊ۉe�n���h��

	int m_animNum;			// �A�j���[�V�����̔ԍ�
	int m_blowRate;			// ������ї�

	// float
	float m_playerAngle2;	// �v���C���[�A���O��
	float m_playerAngleY;	// �v���C���[��Y����]
	float m_cameraAngle;	// �J�����A���O��

	float m_animTotalTime;	// �A�j���[�V�����̑S�̃t���[��
	float m_animPlay;		// �A�j���[�V�����̍Đ�

	float m_jumpAcc;		// �W�����v�����x

	// bool
	bool m_pressUp;			// ��L�[���������������ǂ���
	bool m_pressDown;		// ���L�[���������������ǂ���
	bool m_pressRight;		// �E�L�[���������������ǂ���
	bool m_pressLeft;		// ���L�[���������������ǂ���

	bool m_isJump;			// �W�����v���Ă��邩�ǂ���
	bool m_isMove;			// �����Ă��邩�ǂ���
	bool m_isFall;			// �X�e�[�W�O�ɏo�����ǂ���

	XINPUT_STATE m_input;// �p�b�h��Ԏ擾�ϐ�
};

