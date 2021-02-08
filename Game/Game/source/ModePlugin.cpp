
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModePlugin.h"

bool ModePlugin::Initialize() {
	if (!base::Initialize()) { return false; }

	//	_cg = ResourceServer::LoadGraph("res/.png");

	return true;
}

bool ModePlugin::Terminate() {
	base::Terminate();
	return true;
}

bool ModePlugin::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_B) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeGame(), 1, "game");
	}
	if (trg & PAD_INPUT_A) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
	}

	return true;
}

bool ModePlugin::Render() {
	base::Render();

	DrawString(0, 0, "プラグイン画面", GetColor(255, 255, 255));

	return true;
}
