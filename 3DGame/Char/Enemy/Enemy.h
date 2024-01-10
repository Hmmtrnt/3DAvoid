// エネミーの処理
#pragma once
#include "EnemyBase.h"
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class Enemy : public EnemyBase
{
public:
	// ロードするモデルを指定→指定されたモデルをロードして生成
	Enemy(std::shared_ptr<Player> pPlayer);

	// すでにロードされているモデルのハンドルを指定→Duplicateして生成
	Enemy(int orgModel, int roundShadow, std::shared_ptr<Player> pPlayer);

	// タイトル画面で使用
	Enemy();
	// 二体目以降を複製
	Enemy(int orgModel);

	virtual ~Enemy();

	void Update();
	void Draw();
	
	void UpdateTitle();	// タイトルの動き
	void DrawTitle();	// エネミーのタイトル画面の描画

	bool ColFlag();		// 当たり判定のテスト

// 関数
private:
	void UpdateMove();	// エネミーの動き
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
	std::shared_ptr<Model> m_pModel;	// モデル
	std::shared_ptr<Player> m_pPlayer;	// プレイヤー
};

