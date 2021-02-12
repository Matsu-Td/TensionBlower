
/**
 * @file  ApplicationMain.cpp
 * @brief �A�v���P�[�V�������C��
 *
 * @date 2021-02-08
 */


#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeGame.h"

// ����
ApplicationMain	g_oApplicationMain;

/**
 * ������
 */
bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// �A�v���P�[�V�����O���[�o���̏�����
	gGlobal.Init();

	// ���[�h�̓o�^
	ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");

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

