/**
 * @file   ApplicationMain.cpp
 * @brief  �A�v���P�[�V�������C��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Sound.h"
#include "PlayerVoice.h"
#include "BossVoice.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeAmgLogo.h"
#include "ModeTeamLogo.h"

// ����
ApplicationMain	g_oApplicationMain;

/**
 * ������
 */
bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// �O���[�o���ϐ��̏�����
	gGlobal.Init();
	gSound.Init();
	gPlayerVoice.Init();
	gBossVoice.Init();

	// ���[�h�̓o�^
	ModeServer::GetInstance()->Add(NEW ModeAmgLogo(), 1, "amglogo");

	return true;
}

/**
 * ���
 */
bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}

/**
 * �t���[�������F����
 */
bool ApplicationMain::Input() {
	base::Input();
	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ApplicationMain::Process() {
	base::Process();
	return true;
}

/**
 * �t���[�������F�`��
 */
bool ApplicationMain::Render() {
	base::Render();
	return true;
}

