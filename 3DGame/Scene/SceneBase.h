#pragma once
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init() = 0;// 初期化
	virtual void End() = 0;// 終了処理
	virtual SceneBase* Update() { return this; }// 更新処理
	virtual void Draw() = 0;// 描画

	// フェード関連
	void UpdateFade();// フェード更新
	void DrawFade() const;// フェード描画
	bool IsFadingIn() const;// フェードイン中
	bool IsFadingOut() const;// フェードアウト中
	bool IsFading() const { return IsFadingIn() || IsFadingOut(); }// フェードインorアウト中

	void StartFadeOut();// フェードアウト開始

protected:
	// フェード関連処理
	int m_fadeColor;
	int m_fadeBright;
	int m_fadeSpeed;

	bool m_isFadeOut;// フェードアウトを行っているかどうか

	bool m_isBackScene;
};

