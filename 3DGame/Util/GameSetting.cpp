#include "GameSetting.h"

// 3D�֘A�̐ݒ�
void GameSetting::Init3D()
{
	// Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);
	// �|���S���̗��ʂ�`�悵�Ȃ�
	SetUseBackCulling(true);
}

//�J�����̐ݒ�
void GameSetting::InitCamera()
{
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(VGet(0, 1600, -300), VGet(0.0f, 0.0f, -100.0f));
}
