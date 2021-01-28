
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"


bool ModeGameOver::Initialize() 
{
	if (!base::Initialize()) { return false; }

	_cgGameOver = ResourceServer::LoadGraph("res/仮素材/ゲームオーバー.png");
	gGlobal._gameTime = GetNowCount() - gGlobal._gameTime;
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

		ModeTitle* modeTitle = new ModeTitle();
		ModeServer::GetInstance()->Add(modeTitle, 1, "title");
	}

	return true;
}

bool ModeGameOver::Render()
{
	base::Render();

	DrawGraph(0, 0, _cgGameOver, FALSE);

	return true;
}