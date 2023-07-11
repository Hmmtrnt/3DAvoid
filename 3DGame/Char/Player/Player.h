#pragma once
#include "../../Util/common.h"
#include <memory>

class Model;
class Enemy;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();// 初期化
	void End();// 終了
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="Hitting">当たっている</param>
	void Update(bool Hitting);
	void Draw();// 描画
	
	void UpdateHitDamage(VECTOR enemyPos, bool hit);// ダメージ
	void UpdateHitVec();// エネミーとプレイヤーが当たったときの処理

	// プレイヤーの座標取得
	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }

	// プレイヤーのHP取得
	int GetBlowRate()const { return m_blowRate; }

	// 落ちているかどうかの真偽
	bool GetIsFall()const { return m_isFall; }
	
private:// 関数
	void UpdateNoHitVec(bool Hitting);// 移動処理
	void UpdateMotion(bool hit);
	void UpdateMove(bool Hitting);// キャラクターの動き+α

	void PadInputState();// パッドの入力状態取得
	
	// メンバ関数ポインタ
	//void (Player::* m_updateFunc)();
	
private:// 変数
	// ポインタ
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Player> m_pPlayer;

	// VECTOR
	VECTOR m_pos;		// プレイヤー座標
	VECTOR m_vec;		// プレイヤーの移動
	VECTOR m_hitVec;	// 当たった時のプレイヤーの移動
	VECTOR m_angle;		// プレイヤーアングル
	VECTOR m_move;		// プレイヤーの動き
	VECTOR m_testVec = VGet(50.0f, 0.0f, 50.0f);	// テスト移動

	// MATRIX
	MATRIX m_cameraRotMtx;	// 水平移動の行列取得
	MATRIX m_playerRotMtx;	// プレイヤーの進行方向

	// int
	int m_playerHandle;		// キャラクターハンドル
	int m_AnimNum;			// アニメーションの番号
	int m_blowRate;			// 吹っ飛び率

	// float
	float m_playerAngle2;	// プレイヤーアングル
	float m_playerAngleY;	// プレイヤーのY軸回転
	float m_cameraAngle;	// カメラアングル

	float m_AnimTotalTime;	// アニメーションの全体フレーム
	float m_AnimPlay;		// アニメーションの再生

	float m_jumpAcc;		// ジャンプ加速度

	// bool
	bool m_pressUp;			// 上キーを押し続けたかどうか
	bool m_pressDown;		// 下キーを押し続けたかどうか
	bool m_pressRight;		// 右キーを押し続けたかどうか
	bool m_pressLeft;		// 左キーを押し続けたかどうか

	bool m_isJump;			// ジャンプしているかどうか
	bool m_isMove;			// 動いているかどうか
	bool m_isFall;			// ステージ外に出たかどうか

	// テスト
	XINPUT_STATE input;// パッド状態取得変数
};

