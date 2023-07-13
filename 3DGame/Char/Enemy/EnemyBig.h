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

	EnemyBig();

	virtual ~EnemyBig();

	void Update(int score);
	void Draw();

	void UpdateMove(int score);// エネミーの動き
	void UpdateTitle();// タイトルの動き

	bool ColFlag();// 当たり判定のテスト

// 関数
private:
	/// <summary>
	/// 座標、回転、大きさ設定
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">大きさ</param>
	void InitState(VECTOR pos, VECTOR rot, VECTOR scale);

// 変数
private:
	// ポインタ
	std::shared_ptr<Model> m_pModel;// モデル
	std::shared_ptr<Player> m_pPlayer;// プレイヤー

	// int
	int m_randAngleType;	// エネミーがステージ外に出た時のアングルタイプ

	// bool 
	bool m_initPos;		// 座標を初期化したかどうか
};

