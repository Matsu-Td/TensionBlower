
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeResult.h"

bool ModeResult::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

bool ModeResult::Terminate() {
	base::Terminate();
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

	DrawString(0, 0, "ƒŠƒUƒ‹ƒg‰æ–Ê", GetColor(255, 255, 255));

	return true;
}