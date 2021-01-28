
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
	int size =64;
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	DrawString(0, y, "ƒŠƒUƒ‹ƒg‰æ–Ê", GetColor(255, 255, 255)); y += size;
	DrawFormatString(0, y, GetColor(255, 255, 255), "Œo‰ßŽžŠÔ : %d•b",gGlobal._gameTime / 1000);
	return true;
}