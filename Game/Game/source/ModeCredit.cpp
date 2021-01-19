
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeCredit.h"

bool ModeCredit::Initialize() {
	if (!base::Initialize()) { return false; }

//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

bool ModeCredit::Terminate() {
	base::Terminate();
	return true;
}

bool ModeCredit::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_A) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeCredit::Render() {
	base::Render();

	DrawString(0, 0, "クレジット画面", GetColor(255, 255, 255));

	return true;
}
