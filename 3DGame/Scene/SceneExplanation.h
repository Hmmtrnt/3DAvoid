#pragma once
#include "SceneBase.h"
#include <memory>
#include <DxLib.h>
#include "../Util/game.h"

class BackDrop;

class SceneExplanation : public SceneBase
{
public:
	SceneExplanation();
	virtual ~SceneExplanation();

	void Init();
	void End();
	SceneBase* Update();
	void Draw();

private:
	std::shared_ptr<BackDrop> m_pBackDrop;// �w�i
	int m_handle;// ������ʂ̃n���h��
	int m_handleMove;// ��������̃n���h��

	// ���W
	int m_posX;
	int m_posY;

};

