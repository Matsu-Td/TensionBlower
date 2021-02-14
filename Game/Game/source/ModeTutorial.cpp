
/**
 * @file  ModeTutorial.cpp
 * @brief �`���[�g���A�����
 *
 * @date 2021-02-08
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeTutorial.h"

/**
 * ������
 */
bool ModeTutorial::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/���f��/tutorial.png");

	return true;
}

/**
 * ���
 */
bool ModeTutorial::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeTutorial::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�uA�v�{�^���Ń`���[�g���A�����[�h���폜���A
	// �^�C�g�����[�h�ǉ�
	if (trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeTutorial::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}
