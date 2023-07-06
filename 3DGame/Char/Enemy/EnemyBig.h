#pragma once
// でかいエネミーの処理
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class EnemyBig
{
public:
	// ロードするモデルを指定→指定されたモデルをロードして生成
	EnemyBig(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// すでにロードされているモデルのハンドルを指定→Duplicateして生成
	EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer, int num);

	virtual ~EnemyBig();

	void Init();
	void End();
	void Update();
	void Draw();

	void UpdateMove();// エネミーの動き

	void DebugDraw();// デバッグ用描画

	bool ColFlag();// 当たり判定のテスト

	// モデルの取得
	int GetModelHandle()const;

	// 当たり判定の半径
	float GetColRadius();

	// エネミーの位置取得
	VECTOR GetPos()const { return m_pos; }

	// 当たった時の処理
	void SetPlayerPos(VECTOR playerPos);

	// メンバ関数ポインタ
	void(EnemyBig::* m_updateFunc)();

private:
	// ポインタ
	std::shared_ptr<Model> m_pModel;// モデル
	std::shared_ptr<Player> m_pPlayer;// プレイヤー

	// VECTOR
	VECTOR m_pos;		// エネミー座標
	VECTOR m_dir;		// エネミーの方向
	VECTOR m_vec;		// エネミーの移動

	// float
	float m_angle;		// エネミーのアングル
	float m_speed;		// エネミーのスピード

	// int
	int m_modelHandle;	// エネミーのモデルハンドル
	int m_Number;
};

