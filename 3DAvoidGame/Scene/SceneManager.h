// �V�[���}�l�[�W���[
#pragma once

class SceneBase;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager() {}

	void Init();		// ������
	void End();			// �I��
	void Update();		// ���t���[���̏���
	void Draw();		// �`��

private:
	// �V�[���x�[�X�|�C���^
	SceneBase* m_pScene;
};