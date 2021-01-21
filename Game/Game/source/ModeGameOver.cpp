
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeResult.h"


bool ModeGameOver::Initialize() 
{
	if (!base::Initialize()) { return false; }

	_cgGameOver = ResourceServer::LoadGraph("res/仮素材/ゲームオーバー.png");

	return true;
}

bool ModeGameOver::Terminate()
{
	base::Terminate();

	return true;
}

bool ModeGameOver::Process()
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

bool ModeGameOver::Render()
{
	base::Render();

	DrawGraph(0, 0, _cgGameOver, FALSE);

	return true;
}