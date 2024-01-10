// プレイヤー
#pragma once
#include "../../Util/common.h"
#include <memory>

class Model;
class Enemy;
class SoundManager;

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
	void RoundShadow();// プレイヤーの丸影

	void UpdateTitle();// タイトル画面のプレイヤーの更新処理
	void UpdateResult();// リザルト画面のプレイヤーの更新処理

	void DrawUI(int color, int fontHandle);// プレイヤーのUIを描画

	// プレイヤーの座標取得
	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }

	// プレイヤーのHP取得
	int GetBlowRate()const { return m_blowRate; }

	// 落ちているかどうかの真偽
	bool GetIsFall()const { return m_isFall; }
	
// 関数
private:
	void UpdateNoHitVec(bool Hitting);// 移動処理
	void UpdateMotion(bool hit);
	void UpdateMove(bool Hitting);// キャラクターの動き
	void PadInputState();// パッドの入力状態取得

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
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<SoundManager> m_pSound;// 音楽

	// VECTOR
	VECTOR m_pos;		// プレイヤー座標
	VECTOR m_vec;		// プレイヤーの移動
	VECTOR m_hitVec;	// 当たった時のプレイヤーの移動
	VECTOR m_angle;		// プレイヤーアングル
	VECTOR m_move;		// プレイヤーの動き
	VECTOR m_scale;		// 大きさ

	// MATRIX
	MATRIX m_cameraRotMtx;	// 水平移動の行列取得
	MATRIX m_playerRotMtx;	// プレイヤーの進行方向の行列

	// int
	int m_playerHandle;		// キャラクターハンドル
	int m_roundShadowHandle;// キャラクターの丸影ハンドル

	int m_animNum;			// アニメーションの番号
	int m_blowRate;			// 吹っ飛び率

	// float
	float m_playerAngle2;	// プレイヤーアングル
	float m_playerAngleY;	// プレイヤーのY軸回転
	float m_cameraAngle;	// カメラアングル

	float m_animTotalTime;	// アニメーションの全体フレーム
	float m_animPlay;		// アニメーションの再生

	float m_jumpAcc;		// ジャンプ加速度

	// bool
	bool m_pressUp;			// 上キーを押し続けたかどうか
	bool m_pressDown;		// 下キーを押し続けたかどうか
	bool m_pressRight;		// 右キーを押し続けたかどうか
	bool m_pressLeft;		// 左キーを押し続けたかどうか

	bool m_isJump;			// ジャンプしているかどうか
	bool m_isMove;			// 動いているかどうか
	bool m_isFall;			// ステージ外に出たかどうか

	XINPUT_STATE m_input;// パッド状態取得変数
};

