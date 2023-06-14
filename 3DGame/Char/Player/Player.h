#pragma once
#include "../../Util/common.h"
#include <memory>

class Model;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	
private:// 関数
	void UpdatePlayerPos();// キャラクター操作
	void UpdateCamera();// カメラの更新処理
	void UpdateVec();// キャラクターの加速度
	void UpdateIdle();// キャラクターのアイドル状態

	//--------------------------------------------------------
	// テスト関数
	//--------------------------------------------------------
	void TestMove();// キャラクターの動き+α


	// メンバ関数ポインタ
	void (Player::* m_updateFunc)();
	
private:// 変数
	// ポインタ
	std::shared_ptr<Model> m_pModel;

	// VECTOR
	VECTOR m_playerPos;		// プレイヤー座標
	VECTOR m_playerAngle;	// プレイヤーアングル
	VECTOR m_playerVec;		// プレイヤーの移動
	VECTOR m_playerMove;	// プレイヤーの動き

	// MATRIX
	MATRIX m_cameraRotMtx;	// 水平移動の行列取得
	MATRIX m_playerRotMtx;	// プレイヤーの進行方向

	// int
	int m_playerHandle;		// キャラクターハンドル
	int m_AnimNum;			// アニメーションの番号

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

	// テスト
	int m_frameCount;

	int m_animPrev;//前
	int m_animNext;//後ろ

	
};

