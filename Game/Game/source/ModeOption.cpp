
#include "ApplicationMain.h"
#include "ModeOption.h"

bool ModeOption::Initialize()
{
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/仮素材/ポーズ.png");

	return true;
}

bool ModeOption::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeOption::Process()
{
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (trg & PAD_INPUT_8 || trg & PAD_INPUT_1) {
		// このモードを削除する
		ModeServer::GetInstance()->Del(this);
	}
	return true;
}

bool ModeOption::Render()
{
	base::Render();
	// DrawString(128, 128, "ModeMenu", GetColor(255, 0, 0));
	DrawGraph(0, 0, _cg, TRUE);
	return true;
}