
/**
 * @file  ModeCredit.cpp
 * @brief �N���W�b�g���
 *
 * @date 2021-02-09
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeCredit.h"

/**
 * ������
 */
bool ModeCredit::Initialize() {
	if (!base::Initialize()) { return false; }

//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

/**
 * ���
 */
bool ModeCredit::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeCredit::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�uA�v�{�^���ŃN���W�b�g���[�h���폜���^�C�g�����[�h�ǉ�
	if (trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeCredit::Render() {
	base::Render();
	
	// ������
	DrawString(0, 0, "�N���W�b�g���", GetColor(255, 255, 255));

	return true;
}
