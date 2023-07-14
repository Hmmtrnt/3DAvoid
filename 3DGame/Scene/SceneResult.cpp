#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/common.h"
#include "../Util/FontFunction.h"
#include "../Stage/BackDrop.h"
#include <fstream>
#include <string>
#include <iostream>

SceneResult::SceneResult(int score) :
	m_score(score),
	m_scoreWriting(0),
	m_highScore(0),
	m_fontHandle(-1)
{
	m_pFont = std::make_shared<StringInit>();
	m_pBackDrop = std::make_shared<BackDrop>();
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	m_pFont->Init(m_fontHandle, 80, 0, -1);
}

void SceneResult::End()
{
	m_pFont->End(m_fontHandle);
}

SceneBase* SceneResult::Update()
{
	m_pBackDrop->Update();
	
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			if (m_score > m_highScore)
			{
				GenerationFile();
			}
			return (new SceneMain);
		}
	}

	if (!IsFading())
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
		}
	}

	return this;
}

void SceneResult::Draw()
{
	m_pBackDrop->Draw();

	// �X�R�A�`��(��)
	//m_pFont->DrawFormat(10, 50, Color::kWhite, "YOUSCORE :%d", m_score);
	DrawFormatStringToHandle(10, 50, Color::kWhite, m_fontHandle, "YOUSCORE :%d", m_score);
	ReadFile();

	// �t�F�[�h�C���A�E�g�̃t�B���^�[
	SceneBase::DrawFade();
}

// �t�@�C���̐�����������
void SceneResult::GenerationFile()
{
	std::ofstream writing_file;
	std::string filename = "scoreData.txt";
	writing_file.open(filename, std::ios::out);
	m_scoreWriting = m_score;
	writing_file << m_scoreWriting << std::endl;
	writing_file.close();
}

// �t�@�C���̓ǂݍ���
void SceneResult::ReadFile()
{
	std::ifstream reading_file;
	std::string filename = "scoreData.txt";
	reading_file.open(filename, std::ios::in);
	std::string reading_line_buffer;
	while (std::getline(reading_file, reading_line_buffer)) {
		//std::cout << reading_line_buffer << std::endl;
		//DrawFormatString(0,120,Color::kWhite, "%d", reading_line_buffer);
		// string�^��int�^��
		m_highScore = atoi(reading_line_buffer.c_str());

		//m_pFont->DrawFormat(10, 120, Color::kWhite, "HIGHSCORE:%d", m_highScore);
		DrawFormatStringToHandle(10, 120, Color::kWhite, m_fontHandle,"HIGHSCORE:%d", m_highScore);
	}
}
