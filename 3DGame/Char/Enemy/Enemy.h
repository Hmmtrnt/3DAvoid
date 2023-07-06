#pragma once
// �G�l�~�[�̏���
#include "EnemyBase.h"
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class Enemy : public EnemyBase
{
public:
	// ���[�h���郂�f�����w�聨�w�肳�ꂽ���f�������[�h���Đ���
	Enemy(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// ���łɃ��[�h����Ă��郂�f���̃n���h�����w�聨Duplicate���Đ���
	Enemy(int orgModel, std::shared_ptr<Player> pPlayer);

	virtual ~Enemy();

	void Update();
	void Draw();

	void UpdateMove();// �G�l�~�[�̓���

	bool ColFlag();// �����蔻��̃e�X�g

private:
	// �|�C���^
	std::shared_ptr<Model> m_pModel;// ���f��
	std::shared_ptr<Player> m_pPlayer;// �v���C���[

	

};

