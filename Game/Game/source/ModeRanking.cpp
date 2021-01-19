
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeRanking.h"

bool ModeRanking::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

bool ModeRanking::Terminate() {
	base::Terminate();
	return true;
}

bool ModeRanking::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_A) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeRanking::Render() {
	base::Render();

	DrawString(0, 0, "ƒ‰ƒ“ƒLƒ“ƒO‰æ–Ê", GetColor(255, 255, 255));

	return true;
}
