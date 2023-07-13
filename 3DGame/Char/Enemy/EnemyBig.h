#pragma once
// �ł����G�l�~�[�̏���
#include "EnemyBase.h"
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class EnemyBig : public EnemyBase
{
public:
	// ���[�h���郂�f�����w�聨�w�肳�ꂽ���f�������[�h���Đ���
	EnemyBig(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// ���łɃ��[�h����Ă��郂�f���̃n���h�����w�聨Duplicate���Đ���
	EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer);

	EnemyBig();

	virtual ~EnemyBig();

	void Update(int score);
	void Draw();

	void UpdateMove(int score);// �G�l�~�[�̓���
	void UpdateTitle();// �^�C�g���̓���

	bool ColFlag();// �����蔻��̃e�X�g

// �֐�
private:
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
	std::shared_ptr<Model> m_pModel;// ���f��
	std::shared_ptr<Player> m_pPlayer;// �v���C���[

	// int
	int m_randAngleType;	// �G�l�~�[���X�e�[�W�O�ɏo�����̃A���O���^�C�v

	// bool 
	bool m_initPos;		// ���W���������������ǂ���
};

