// �R���g���[���[
// ���Ƃ̃R�[�h�T���v�����Q�l
#pragma once
#include "DxLib.h"

// �R���g���[���[����̓��͏�Ԃ��擾����
namespace Pad
{
	void Update();					// �p�b�h�̓��͏�Ԏ擾
	bool IsPress(int button);		// ������������
	bool IsTrigger(int button);		// �g���K�[����
	bool IsRelase(int button);		// ����������
}