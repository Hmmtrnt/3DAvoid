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

	// モデルの取得
	int GetModelHandle()const;

	// 当たり判定の半径
	float GetColRadius();

	// エネミーの位置取得
	VECTOR GetPos()const { return m_pos; }

	// メンバ関数ポインタ
	void(Enemy::* m_updateFunc)();

private:
	// ポインタ
	std::shared_ptr<Model> m_pModel;// モデル
	std::shared_ptr<Player> m_pPlayer;// プレイヤー

	// VECTOR
	VECTOR m_pos;		// エネミー座標

	// float
	float m_angle;		// エネミーのアングル

	// int
	int m_modelHandle;	// エネミーのモデルハンドル

	// vector
	//std::vector<int> m_enemies;// エネミーの数
};

