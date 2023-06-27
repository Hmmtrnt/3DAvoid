#pragma once
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class Enemy
{
public:
	// ロードするモデルを指定→指定されたモデルをロードして生成
	Enemy(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// すでにロードされているモデルのハンドルを指定→Duplicateして生成
	Enemy(int orgModel, std::shared_ptr<Player> pPlayer);

	virtual ~Enemy();

	void Init();
	void End();
	void Update();
	void Draw();

	void UpdateMove();// エネミーの動き

	void UpdateHit(int playerHp, bool hit);// エネミーとプレイヤーが当たったときの処理

	bool ColFlag();// 当たり判定のテスト

	// モデルの取得
	int GetModelHandle()const;

	// 当たり判定の半径
	float GetColRadius();

	// エネミーの位置取得
	VECTOR GetPos()const { return m_pos; }

	// 当たり判定の真偽取得
	bool GetIsCol()const { return m_isCol; }

	// 当たった時の処理
	void SetPlayerPos(VECTOR playerPos);

	// メンバ関数ポインタ
	void(Enemy::* m_updateFunc)();

private:
	// ポインタ
	std::shared_ptr<Model> m_pModel;// モデル
	std::shared_ptr<Player> m_pPlayer;// プレイヤー

	// VECTOR
	VECTOR m_pos;		// エネミー座標
	VECTOR m_dir;		// エネミーの方向
	VECTOR m_vec;		// エネミーの移動
	VECTOR m_playerPos;	// プレイヤーの当たった時の座標
	VECTOR m_testPlayerVec = VGet(0.0f, 0.0f, 0.0f);// プレイヤーのベクトル

	// float
	float m_angle;		// エネミーのアングル
	

	// int
	int m_modelHandle;	// エネミーのモデルハンドル
	int m_playerHandle;

	// bool
	bool m_isCol;// エネミーの当たり判定の真偽

	// vector
	//std::vector<int> m_enemies;// エネミーの数

	MV1_COLL_RESULT_POLY_DIM test;
};

