#include "Scaffold.h"
#include "../Char/Model.h"
#include <cassert>

namespace
{
	// ƒ‚ƒfƒ‹ID
	const char* const kModelId = "Data/3D/Field/Scaffold.mv1";

	const float kScaleNum = 50.0f;
	// ‘å‚«‚³
	const VECTOR kScale = VGet(kScaleNum, kScaleNum, kScaleNum);
}

Scaffold::Scaffold() :
	m_modelHandle(-1)
{
	m_modelHandle = MV1LoadModel(kModelId);

	m_pModel = std::make_shared<Model>(m_modelHandle);
	assert(m_modelHandle != -1);
}

Scaffold::~Scaffold()
{
}

void Scaffold::Update()
{
	m_pModel->SetPos(VGet(-50.0f,50.0f,0.0f));
	m_pModel->SetRot(VGet(-0.3f, 0.0f, 0.0f));
	m_pModel->SetScale(kScale);
}

void Scaffold::Draw()
{
	m_pModel->Draw();
}
