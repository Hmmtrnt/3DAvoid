// �X�e�[�W
#pragma once
#include <vector>
#include <memory>

class Model;

class Field
{
public:
	Field();
	virtual ~Field();

	void DrawMain();	// ���C���V�[���̕`��
	void DrawTitle();	// �^�C�g���V�[���̕`��

private:
	// �|�C���^
	std::vector<std::shared_ptr<Model>> m_pModel;// ���f��
};

