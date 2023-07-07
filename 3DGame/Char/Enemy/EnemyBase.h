#pragma once
// エネミーベース
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	void Init(){}
	void End(){}
	void Update(){}
	void Draw(){}

	// エネミーの動き
	void EnemyMove();

	// モデルの取得
	int GetModelHandle()const;

	// エネミーの位置取得
	VECTOR GetPos()const { return m_pos; }

protected:
	// VECTOR
	VECTOR m_pos;		// エネミー座標
	VECTOR m_dir;		// エネミーの方向
	VECTOR m_vec;		// エネミーの移動
	VECTOR m_scale;		// エネミーの大きさ
	VECTOR m_EnemyDir;	// エネミーの向く方向

	// float
	float m_angle;		// エネミーのアングル
	float m_speed;		// エネミーのスピード

	// int
	int m_modelHandle;	// エネミーのモデルハンドル
	int m_animMove;		// エネミーのモーション番号
};

