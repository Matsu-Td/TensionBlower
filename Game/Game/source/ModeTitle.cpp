
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeTitle::Terminate() {
	base::Terminate();
	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_A)	{
		// ‚±‚Ìƒ‚[ƒh‚ğíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// Ÿ‚Ìƒ‚[ƒh‚ğ“o˜^
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();

	DrawString(16, 16, "–À˜HƒQ[ƒ€", GetColor(255, 255, 255));

	return true;
}

