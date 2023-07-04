#include "Wall.h"
#include "../Char/Model.h"
#include "DxLib.h"

namespace
{
	// ���f���̃t�@�C����
	const char* const kFileName = "Data/Field/Field2(toonType2).mv1";
	// �n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 10;
	constexpr int kBlockNumZ = 10;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	// �u���b�N��1�ӂ̒���
	constexpr float kBlockSideLenght = 200.0f;

	// �n��1�ӂ̒���
	constexpr float kFieldSideLenghtX = kBlockSideLenght * kBlockNumX;
	constexpr float kFieldSideLenghtZ = kBlockSideLenght * kBlockNumZ;
}

Wall::Wall()
{
	// 3D���f�������[�h����
	m_pModel.push_back(std::make_shared<Model>(kFileName));

	// �ŏ��Ƀ��[�h�������f���ƍ��킹�ă��f����100����
	int orgModel = m_pModel[0]->getModelHandle();
	for (int i = 0; i < kBlockNum - 1; i++)					//�ŏ��ɐ�������1�������Ă�����
	{
		m_pModel.push_back(std::make_shared<Model>(orgModel));
	}
	// �n�ʂɕ��ׂ�
	for (int i = 0; i < m_pModel.size(); i++)
	{
		float x = kBlockSideLenght * (i % kBlockNumX) - 
			kFieldSideLenghtX / 2 + kBlockSideLenght / 2;			//�n�ʂ̈ʒu�������悤�ɐݒ�
		float z = kBlockSideLenght * (i / kBlockNumX) - 
			kFieldSideLenghtX / 2 + kBlockSideLenght / 2;
		m_pModel[i]->SetPos(VGet(x, kBlockSideLenght / 2.0f, z));	// ��ʂ� y =0.0�ɂȂ�悤�ɔz�u
	}
}

Wall::~Wall()
{
}

void Wall::Init()
{
}

void Wall::End()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
	for (auto& model : m_pModel)
	{
		model->Draw();
	}
}
