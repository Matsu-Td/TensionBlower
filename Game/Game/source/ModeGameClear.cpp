
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeResult.h"


bool ModeGameClear::Initialize()
{
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/‰¼‘fÞ/ƒQ[ƒ€ƒNƒŠƒA.png");
	gGlobal._gameTime = GetNowCount() - gGlobal._gameTime;

	return true;
}

bool ModeGameClear::Terminate()
{
	base::Terminate();

	return true;
}

bool ModeGameClear::Process()
{
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (trg & PAD_INPUT_2) {

		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

		ModeResult* modeResult = new ModeResult();
		ModeServer::GetInstance()->Add(modeResult, 1, "result");

	}

	return true;
}

bool ModeGameClear::Render()
{
	base::Render();

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}