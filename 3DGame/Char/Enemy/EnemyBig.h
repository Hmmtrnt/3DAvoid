#pragma once
// でかいエネミーの処理
#include "EnemyBase.h"
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class EnemyBig : public EnemyBase
{
public:
	// ロードするモデルを指定→指定されたモデルをロードして生成
	EnemyBig(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// すでにロードされているモデルのハンドルを指定→Duplicateして生成
	EnemyBig(int orgModel, std::shared_ptr<Player> pPlayer);

	virtual ~EnemyBig();

	void Update(int score);
	void Draw();

	void UpdateMove(int score);// エネミーの動き

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

	// int
	int m_randAngleType;	// エネミーがステージ外に出た時のアングルタイプ

	// bool 
	bool m_initPos;		// 座標を初期化したかどうか
};

