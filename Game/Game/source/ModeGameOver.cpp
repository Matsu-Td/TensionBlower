
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"


bool ModeGameOver::Initialize() 
{
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/���f��/�Q�[���I�[�o�[.png");

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

	DrawGraph(0, 0, _cg, FALSE);

	return true;
}