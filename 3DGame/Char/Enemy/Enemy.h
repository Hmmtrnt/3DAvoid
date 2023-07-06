#pragma once
// エネミーの処理
#include "EnemyBase.h"
#include "../../Util/common.h"
#include <memory>

class Player;
class Model;

class Enemy : public EnemyBase
{
public:
	// ロードするモデルを指定→指定されたモデルをロードして生成
	Enemy(/*const char* fileName, */std::shared_ptr<Player> pPlayer);

	// すでにロードされているモデルのハンドルを指定→Duplicateして生成
	Enemy(int orgModel, std::shared_ptr<Player> pPlayer);

	virtual ~Enemy();

	void Update();
	void Draw();

	void UpdateMove();// エネミーの動き

	bool ColFlag();// 当たり判定のテスト

private:
	// ポインタ
	std::shared_ptr<Model> m_pModel;// モデル
	std::shared_ptr<Player> m_pPlayer;// プレイヤー

	

};

