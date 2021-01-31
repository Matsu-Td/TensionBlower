
#include "ApplicationMain.h"
#include "ModeOption.h"
#include "ModeTitle.h"

bool ModeOption::Initialize()
{
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/仮素材/ポーズ.png");
	_ui[0] = ResourceServer::LoadGraph("res/ui/on/title_on_1.png");
	_ui[1] = ResourceServer::LoadGraph("res/ui/on/title_on_6.png");
	_ui[2] = ResourceServer::LoadGraph("res/ui/off/title_off_1.png");
	_ui[3] = ResourceServer::LoadGraph("res/ui/off/title_off_6.png");

	_menuPos = 0;
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

	if (_menuPos == 0) {
		if (trg & PAD_INPUT_DOWN) {
			_menuPos++;
		}
		if (trg & PAD_INPUT_2) {
			// このモードを削除する
			ModeServer::GetInstance()->Del(this);
		}
	}
	if (_menuPos == 1) {
		if (trg & PAD_INPUT_UP) {
			_menuPos--;
		}
		if (trg & PAD_INPUT_2) {
			// このモードを削除する
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

			ModeTitle* modeTitle = new ModeTitle();
			ModeServer::GetInstance()->Add(modeTitle, 1, "title");
		}
	}

	return true;
}

bool ModeOption::Render()
{
	base::Render();
	// DrawString(128, 128, "ModeMenu", GetColor(255, 0, 0));
	DrawGraph(0, 0, _cg, TRUE);

	if (_menuPos == 0) {
		DrawGraph(786, 380, _ui[0], TRUE);
		DrawGraph(786, 580, _ui[3], TRUE);
	}
	if (_menuPos == 1) {
		DrawGraph(786, 380, _ui[2], TRUE);
		DrawGraph(786, 580, _ui[1], TRUE);
	}
	return true;
}