#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/common.h"
#include "../Util/FontFunction.h"
#include "../Util/GameSetting.h"
#include "../Stage/BackDrop.h"
#include "../Char/Player/Player.h"
#include <fstream>
#include <string>
#include <iostream>

SceneResult::SceneResult(int score) :
	m_score(score),
	m_scoreWriting(0),
	m_highScore(0),
	m_fontHandle(-1),
	m_oneMore(false)
{
	m_pSet = std::make_shared<GameSetting>();
	m_pFont = std::make_shared<StringInit>();
	m_pBackDrop = std::make_shared<BackDrop>();
	m_pPlayer = std::make_shared<Player>();
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	m_pSet->InitSceneOriginPosCamera();
	m_pFont->Init(m_fontHandle, 80, 0, -1);
}

void SceneResult::End()
{
	m_pFont->End(m_fontHandle);
}

SceneBase* SceneResult::Update()
{
	m_pBackDrop->Update();
	m_pPlayer->UpdateResult();
	// ファイル書き込み
	ReadFile();
	
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene && m_oneMore)
		{
			if (m_score > m_highScore)
			{
				GenerationFile();
			}
			return new SceneMain;
		}
		else if (!IsFading() && m_isFadeOut && !m_isBackScene && !m_oneMore)
		{
			if (m_score > m_highScore)
			{
				GenerationFile();
			}
			return new SceneTitle;
		}
	}

	if (!IsFading())
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
			m_oneMore = true;
		}
		if (Pad::IsTrigger(PAD_INPUT_2))
		{
			StartFadeOut();
			m_oneMore = false;
		}
	}

	

	return this;
}

void SceneResult::Draw()
{
	m_pBackDrop->Draw();
	m_pPlayer->Draw();

	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	DrawBox(Game::kScreenWidth / 2, 100, (Game::kScreenWidth / 2) + 500, 600, Color::kBlack, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// スコア描画(仮)
	//m_pFont->DrawFormat(10, 50, Color::kWhite, "YOUSCORE :%d", m_score);
	DrawFormatStringToHandle(Game::kScreenWidth / 2, 100, Color::kBlack, m_fontHandle, "YOUSCORE\n%d", m_score);
	DrawFormatStringToHandle(Game::kScreenWidth / 2, 340, Color::kBlack, m_fontHandle, "HIGHSCORE\n%d", m_highScore);
	

	// フェードインアウトのフィルター
	SceneBase::DrawFade();
}

// ファイルの生成書き込み
void SceneResult::GenerationFile()
{
	std::ofstream writing_file;
	std::string filename = "scoreData.txt";
	writing_file.open(filename, std::ios::out);
	m_scoreWriting = m_score;
	writing_file << m_scoreWriting << std::endl;
	writing_file.close();
}

// ファイルの読み込み
void SceneResult::ReadFile()
{
	std::ifstream reading_file;
	std::string filename = "scoreData.txt";
	reading_file.open(filename, std::ios::in);
	std::string reading_line_buffer;
	while (std::getline(reading_file, reading_line_buffer)) {
		// string型をint型へ
		m_highScore = atoi(reading_line_buffer.c_str());
	}
}
