// �G�l�~�[�̏���
#pragma once
#include "EnemyBase.h"
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class Enemy : public EnemyBase
{
public:
	// ���[�h���郂�f�����w�聨�w�肳�ꂽ���f�������[�h���Đ���
	Enemy(std::shared_ptr<Player> pPlayer);

	// ���łɃ��[�h����Ă��郂�f���̃n���h�����w�聨Duplicate���Đ���
	Enemy(int orgModel, int roundShadow, std::shared_ptr<Player> pPlayer);

	// �^�C�g����ʂŎg�p
	Enemy();
	// ��̖ڈȍ~�𕡐�
	Enemy(int orgModel);

	virtual ~Enemy();

	void Update();
	void Draw();
	
	void UpdateTitle();	// �^�C�g���̓���
	void DrawTitle();	// �G�l�~�[�̃^�C�g����ʂ̕`��

	bool ColFlag();		// �����蔻��̃e�X�g

// �֐�
private:
	void UpdateMove();	// �G�l�~�[�̓���
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
	std::shared_ptr<Model> m_pModel;	// ���f��
	std::shared_ptr<Player> m_pPlayer;	// �v���C���[
};

