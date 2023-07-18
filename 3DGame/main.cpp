#include "DxLib.h"
#include "Util/game.h"
#include "Scene/SceneManager.h"
#include "Util/GameSetting.h"
#include <memory>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowModo);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);


	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �|�C���^
	std::shared_ptr<SceneManager> pScene;// �V�[��
	pScene = std::make_shared<SceneManager>();
	std::shared_ptr<GameSetting> pSet;// �Q�[����3D�ݒ�
	pSet = std::make_shared<GameSetting>();

	pSet->Init3D();// z�o�b�t�@�L��
	
	pScene->Init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		pScene->Update();
		pScene->Draw();

		// ����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc���[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	pScene->End();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}