#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <vector>
#include <memory>

class GameSetting;
class Player;
class Enemy;
class EnemyBig;
class Field;
class BackDrop;
class SoundManager;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

// 関数
private:
	// void
	// タイトルロゴの更新処理
	void UpdateTitleLogo();
	// インターバルを進める
	void IntervalAdvance(int topNum);

	// bool
	// press any bottonの点滅処理
	bool DrawInterval();
	// ボタンを押したときのインターバル
	bool DrawPushInterval();

// 変数
private:
	// ポインタ
	std::shared_ptr<GameSetting> m_pSet;// 環境設定
	std::shared_ptr<Player> m_pPlayer;// プレイヤー
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// エネミー
	std::shared_ptr<EnemyBig> m_pEnemyBig;// 大きいエネミー
	std::shared_ptr<Field> m_pField;// ステージ
	std::shared_ptr<BackDrop> m_pBackDrop;// 背景
	std::shared_ptr<SoundManager> m_pSound;// 音

	// int
	int m_titleHandle;// タイトルの画像ハンドル
	int m_stringHandle;// 文字列の画像ハンドル
	int m_enemyHandle;// エネミーハンドル
	int m_roundShadowHandle;// 丸影ハンドル
	// タイトル座標
	int m_titlePosX;// X
	int m_titlePosY;// Y
	// タイトル大きさ
	int m_titleScaleX;// 幅
	int m_titleScaleY;// 高さ

	
	int m_drawFlashingInterval;// 点滅描画する時の時間
	int m_topNumInterval;// 点滅描画するときの時間を初期化するタイミング

	// αブレンドのパラメータ
	int m_alphaParameter;

	// bool
	bool m_isDraw;// 描画されるかどうか
	bool m_isPush;// press any bottonが押されたかどうか

	// -------------------------
	// テスト変数
	// -------------------------

	
};

