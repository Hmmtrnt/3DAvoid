#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>
#include <vector>

class GameSetting;
class Player;
class EnemyBase;
class Enemy;
class EnemyBig;
class Field;
class Wall;
class StringInit;
class Pause;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

	// DOTO:関数名変更
	void UpdateEnemy();// 敵に当たった時の更新処理

// 関数
private:
	// ダメージ表記によって色変更
	void UpdateColor();

	// ポーズを押していないときの処理
	void UpdatePauseNo();
	// ポーズを押したときの処理
	void UpdatePause();

	// メンバ関数ポインタ
	void(SceneMain::* m_updateFunc)();

// 変数
private:
	// ポインタ
	std::shared_ptr<GameSetting> m_pSet;// 環境設定
	std::shared_ptr<Player> m_pPlayer;// プレイヤー
	std::shared_ptr<Field> m_pField;// ステージ
	std::shared_ptr<Wall> m_pWall;// 壁
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;// エネミー
	std::vector<std::shared_ptr<EnemyBig>> m_pEnemyBig;// エネミー

	std::vector<std::shared_ptr<EnemyBase>> m_pEnemyTest;// テスト変数エネミー

	std::shared_ptr<StringInit> m_pFont;// フォント
	std::shared_ptr<Pause> m_pPause;

	// int
	int m_shadowMap; // シャドウマップ
	int m_invincibleTime;// プレイヤーの無敵時間
	int m_hpRedColor;// Hpのカラー赤
	unsigned int m_hpColor;// Hpのカラー
	int m_score;// ゲームのスコア
	int m_BackGroundHandle;// 背景のハンドル
	int m_red;// 赤の値
	int m_decreaseColor;// 色が消えていく変数
	int m_enemyModelHandle;// 複製するための敵のコピー
	int m_fontHandle;// フォントハンドル
	int m_selectNum;// ポーズ画面の選択番号

	// bool
	bool m_hit;// 当たったかどうか
	bool m_hitting;// 当たっている
	bool m_pushPause;// ポーズボタンを押したかどうか
	bool m_isNoteOpen;// 注意書きを開いているかどうか


	XINPUT_STATE  input;// パッド状態取得変数
};
