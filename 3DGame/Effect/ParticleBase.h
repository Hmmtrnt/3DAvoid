#pragma once
// パーティクルベース
#include "../Util/common.h"

class ParticleBase
{
public:
	ParticleBase();
	virtual ~ParticleBase();

	void Init();
	void Update();
	void Draw();

	// パーティクル開始
	void Start(VECTOR pos);

	// 設定可能な項目
	void SetPos(VECTOR pos) { m_pos = pos; }// 座標
	void SetVec(VECTOR vec) { m_vec = vec; }// 移動
	void SetRadius(float radius) { m_radius = radius; }// 球の半径

protected:
	// VECTOR
	VECTOR m_pos;// 座標
	VECTOR m_vec;// 移動

	// int
	int m_divNum;// 球を形成するポリゴンの細かさ
	unsigned int m_difColor;// 球の頂点ディフューズカラー
	unsigned int SpcColor;// 球の頂点スペキュラーカラー

	// float
	float m_radius;// 球の半径

	// bool
	bool m_isExist;// 存在しているかどうか

};

