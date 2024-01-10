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

	void Init(){}	// 初期化
	void End(){}	// 終了時
	void Update(){}	// 更新処理
	void Draw(){}	// 描画

	// エネミーの動き
	void EnemyMove();

	// 丸影描画
	void RoundShadow(float y, float scale);

	// モデルの取得
	int GetModelHandle()const;// エネミー
	int GetShadowHandle()const;// 丸影

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
	int m_roundShadowHandle;// 丸影ハンドル
};

