

#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include <memory>



bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }


	SetBackgroundColor(0, 255, 255);
	return true;
}


bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}



bool ModeGame::Process() {
	base::Process();

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	_cam.Process();
	_pl.Process();
	_bs.Process();

	return true;
}


bool ModeGame::Render() {
	base::Render();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	_stg.Render();
	_cam.Render();
	_pl.Render();
	_bs.Render();

	return true;
}

