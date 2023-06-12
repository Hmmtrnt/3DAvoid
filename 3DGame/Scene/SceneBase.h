#pragma once
class SceneBase
{
public:
	SceneBase(){}
	virtual ~SceneBase() {}

	virtual void Init() = 0;// ������
	virtual void End() = 0;// �I������
	virtual SceneBase* Update() { return this; }// �X�V����
	virtual void Draw() = 0;// �`��
};

