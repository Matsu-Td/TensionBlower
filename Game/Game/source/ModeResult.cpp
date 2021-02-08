
/**
 * @file  ModeResult.cpp
 * @brief ���U���g���
 *
 * @date 2021-02-08
 */

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeResult.h"

bool ModeResult::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");
	SetFontSize(64);
	_score = 0;

	return true;
}

bool ModeResult::Terminate() {
	base::Terminate();
	InitFontToHandle();
	return true;
}

bool ModeResult::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_B) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeResult::Render() {
	base::Render();

	int y = 0;
	int size =200;
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawString(0, y, "���U���g���", GetColor(255, 255, 255)); y += 200;
	DrawFormatString(0, y, GetColor(255, 255, 255), "�o�ߎ���           : %d�b", gGlobal._gameTime / 1000); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "�c��̗�           : %d", gGlobal._remainingHP); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "�e���Ԃ���       : %d ��", gGlobal._totalRepelCnt); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "���l���G�l���M�[�� : %d", gGlobal._totalGetEnergy); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "���X�R�A �@�@�@�@�@: %d", _score);
	return true;
}