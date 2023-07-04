#include "Wall.h"
#include "../Char/Model.h"
#include "DxLib.h"

namespace
{
	// モデルのファイル名
	const char* const kFileName = "Data/Field/Field2(toonType2).mv1";
	// 地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 10;
	constexpr int kBlockNumZ = 10;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	// ブロックの1辺の長さ
	constexpr float kBlockSideLenght = 200.0f;

	// 地面1辺の長さ
	constexpr float kFieldSideLenghtX = kBlockSideLenght * kBlockNumX;
	constexpr float kFieldSideLenghtZ = kBlockSideLenght * kBlockNumZ;
}

Wall::Wall()
{
	// 3Dモデルをロードする
	m_pModel.push_back(std::make_shared<Model>(kFileName));

	// 最初にロードしたモデルと合わせてモデルを100個生成
	int orgModel = m_pModel[0]->getModelHandle();
	for (int i = 0; i < kBlockNum - 1; i++)					//最初に精製した1つを引いてあげる
	{
		m_pModel.push_back(std::make_shared<Model>(orgModel));
	}
	// 地面に並べる
	for (int i = 0; i < m_pModel.size(); i++)
	{
		float x = kBlockSideLenght * (i % kBlockNumX) - 
			kFieldSideLenghtX / 2 + kBlockSideLenght / 2;			//地面の位置が合うように設定
		float z = kBlockSideLenght * (i / kBlockNumX) - 
			kFieldSideLenghtX / 2 + kBlockSideLenght / 2;
		m_pModel[i]->SetPos(VGet(x, kBlockSideLenght / 2.0f, z));	// 上面が y =0.0になるように配置
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
