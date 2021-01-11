

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include <memory>



bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	SetBackgroundColor(0, 255, 255);
	_stg = std::make_unique<Stage>();
	_pl = std::make_unique<Player>();
	_bs = std::make_unique<Boss>();

	return true;
}


bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}



bool ModeGame::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	_cam.Process();
	_pl->Update();
	_bs->Update();
	_bltServer.Update();
	if (trg & PAD_INPUT_8) {
		ModeOption* modeOption = new ModeOption();

		ModeServer::GetInstance()->Add(modeOption, 99, "option");
	}

	return true;
}


bool ModeGame::Render() {
	base::Render();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	_stg->Render();
	_pl->Render();
	_bs->Render();
	_cam.Render();
	_bltServer.Render();

	return true;
}

