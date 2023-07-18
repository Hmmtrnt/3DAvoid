#pragma once
#include "SceneBase.h"
#include "../Util/common.h"
#include <memory>

class GameSetting;
class StringInit;
class BackDrop;
class Player;

class SceneResult : public SceneBase
{
public:
	SceneResult(int score);// コンストラクタ
	virtual ~SceneResult();// デストラクタ

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

// 関数
private:
	// ファイルの生成書き込み
	void GenerationFile();

	// ファイルの書き込み
	void ReadFile();
// 変数
private:
	// ポインタ
	std::shared_ptr<GameSetting> m_pSet;// ゲームの設定
	std::shared_ptr<StringInit> m_pFont;// フォント
	std::shared_ptr<BackDrop> m_pBackDrop;// 背景
	std::shared_ptr<Player> m_pPlayer;// プレイヤー

	// int
	int m_score;// ゲームで得たスコア
	int m_scoreWriting;// 高得点のスコアを書き込む
	int m_highScore;// ファイルの中にあるハイスコア
	int m_fontHandle;// フォントハンドル


// -------------------------
// テスト変数
// -------------------------
	bool m_oneMore;// もう一度プレイするかどうか

};

