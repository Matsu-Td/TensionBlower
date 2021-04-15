/**
 * @file   ApplicationMain.cpp
 * @brief  �v���W�F�N�g�̃��C������
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "appFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "../Sound/Sound.h"
#include "../Player/LoadPlayerVoice.h"
#include "../Boss/LoadBossVoice.h"
#include "../Mode/ModeTitle.h"
#include "../Mode/ModeGame.h"
#include "../Mode/ModeAmgLogo.h"
#include "../Mode/ModeTeamLogo.h"

using namespace tensionblower;

// ����
ApplicationMain	g_oApplicationMain;

/*
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
	::mode::ModeServer::GetInstance()->Add(NEW mode::ModeAmgLogo(), 1, "amglogo");

	return true;
}

/*
 * ���
 */
bool ApplicationMain::Terminate() {
	base::Terminate();

	return true;
}

/*
 * �t���[�������F����
 */
bool ApplicationMain::Input() {
	base::Input();

	return true;
}

/*
 * �t���[�������F�v�Z
 */
bool ApplicationMain::Process() {
	base::Process();

	return true;
}

/*
 * �t���[�������F�`��
 */
bool ApplicationMain::Render() {
	base::Render();

	return true;
}

