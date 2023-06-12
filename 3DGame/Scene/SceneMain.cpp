#include "SceneMain.h"
#include "SceneTitle.h"
#include "../Util/GameSetting.h"
#include "../Char/Player/Player.h"
#include "../Stage/Field.h"

namespace
{
	
}

SceneMain::SceneMain()
{
	m_pSet = new GameSetting;
	m_pPlayer = new Player;
	m_pField = new Field;

	test.X = 0;
	test.Y = 0;
	test.Z = 0;
	test.Rx = 0;
	test.Ry = 0;
	test.Rz = 0;
	/*test.Slider[2];
	test.POV[4];
	test.Buttons[32];*/

}

SceneMain::~SceneMain()
{
	delete m_pSet;
	delete m_pPlayer;
	delete m_pField;
}

void SceneMain::Init()
{
	m_pSet->Init3D();
	m_pSet->InitCamera();
	m_pPlayer->Init();
	m_pField->Init();
}

void SceneMain::End()
{
	m_pPlayer->End();
}

SceneBase* SceneMain::Update()
{
	m_pPlayer->Update();
	
	GetJoypadDirectInputState(DX_INPUT_PAD1, &test);

	return this;
}

void SceneMain::Draw()
{
	// -500~500の範囲にグリッドを表示
	for (float x = -500.0f; x <= 500.0f; x += 100.0f)
	{
		VECTOR start = VGet(x, 0.0f, -500.0f);
		VECTOR end = VGet(x, 0.0f, 500.0f);
		DrawLine3D(start, end, GetColor(0, 255, 255));
	}
	for (float z = -500.0f; z <= 500.0f; z += 100.0f)
	{
		VECTOR start = VGet(-500.0f, 0.0f, z);
		VECTOR end = VGet(500.0f, 0.0f, z);
		DrawLine3D(start, end, GetColor(255, 0, 0));
	}

	m_pPlayer->Draw();

	//DrawString(0, 0, "Main", 0xffffff);

	//Color = GetColor(255, 255, 255);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "X:%d Y:%d Z:%d",
		test.X, test.Y, test.Z);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Rx:%d Ry:%d Rz:%d",
		test.Rx, test.Ry, test.Rz);
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Slider 0:%d 1:%d",
		test.Slider[0], test.Slider[1]);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "POV 0:%d 1:%d 2:%d 3:%d",
		test.POV[0], test.POV[1],
		test.POV[2], test.POV[3]);
	DrawString(0, 64, "Button", GetColor(255, 255, 255));
	for (int i = 0; i < 32; i++)
	{
		DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, GetColor(255, 255, 255),
			"%2d:%d", i, test.Buttons[i]);
	}

	//DrawFormatString(0, 30, 0xfffffff, "ジョイパッドX：%d", x);
	//DrawFormatString(0, 60, 0xfffffff, "ジョイパッドY：%d", y);

	m_pField->Draw();
}
