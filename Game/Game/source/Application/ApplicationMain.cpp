/**
 * @file   ApplicationMain.cpp
 * @brief  �v���W�F�N�g�̃��C������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "../Sound/Sound.h"
#include "../Player/PlayerVoice.h"
#include "../Boss/BossVoice.h"
#include "../Mode/ModeTitle.h"
#include "../Mode/ModeGame.h"
#include "../Mode/ModeAmgLogo.h"
#include "../Mode/ModeTeamLogo.h"

// ����
ApplicationMain	g_oApplicationMain;

/**
 * ������
 */
bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// �O���[�o���ϐ��̏�����
	gGlobal.Initialize();
	gSound.Initialize();
	gPlayerVoice.Initialize();
	gBossVoice.Initialize();

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

