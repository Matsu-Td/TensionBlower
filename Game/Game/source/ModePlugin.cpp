
/**
 * @file  ModePlugin.cpp
 * @brief �v���O�C�����
 *
 * @date 2021-02-08
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModePlugin.h"

/**
 * ������
 */
bool ModePlugin::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

/**
 * ���
 */
bool ModePlugin::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModePlugin::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// �Q�[���p�b�h�uB�v�{�^���Ńv���O�C�����[�h�폜���A�Q�[�����[�h�ǉ�
	if (trg & PAD_INPUT_2) {   
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeGame(), 1, "game");
	}
	// �Q�[���p�b�h�uA�v�{�^���Ńv���O�C�����[�h�폜���A�^�C�g�����[�h�ǉ�
	if (trg & PAD_INPUT_1) {  
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModePlugin::Render() {
	base::Render();

	DrawString(0, 0, "�v���O�C�����", GetColor(255, 255, 255));

	return true;
}
