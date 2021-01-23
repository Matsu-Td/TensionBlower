
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include <memory>

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	//SetBackgroundColor(0, 255, 255);
	_charaData = new PlayerData("res/json/", "CharaData");

	_objServer.Add(new Stage());
	_objServer.Add(new Player());
	_objServer.Add(new Boss());

	
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	delete _charaData;
	_objServer.Clear();

	return true;
}

bool ModeGame::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

		_cam.Process();

		_objServer.Process();

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

	_objServer.Render();
	_cam.Render();
	DrawFormatString(500, 200, GetColor(255, 0, 0), "hitpoint=%d", _charaData->_hitpoint);
	return true;
}

