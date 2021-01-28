
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModePlugin.h"
#include "ModeCredit.h"
#include "ModeOption.h"
#include "ModeTutorial.h"
#include "ModeRanking.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	_cgtitle            = ResourceServer::LoadGraph("res/logo_title.png");
	_cg["on_start"]     = ResourceServer::LoadGraph("res/ui/on/title_on_1.png");
	_cg["on_tutorial"]  = ResourceServer::LoadGraph("res/ui/on/title_on_2.png");
	_cg["on_ranking"]   = ResourceServer::LoadGraph("res/ui/on/title_on_3.png");
//	_cg["on_option"]    = ResourceServer::LoadGraph("res/ui/on/title_on_4.png");
	_cg["on_credit"]    = ResourceServer::LoadGraph("res/ui/on/title_on_5.png");
	_cg["on_end"]       = ResourceServer::LoadGraph("res/ui/on/title_on_6.png");
	_cg["off_start"]    = ResourceServer::LoadGraph("res/ui/off/title_off_1.png");
	_cg["off_tutorial"] = ResourceServer::LoadGraph("res/ui/off/title_off_2.png");
	_cg["off_ranking"]  = ResourceServer::LoadGraph("res/ui/off/title_off_3.png");
//	_cg["off_option"]   = ResourceServer::LoadGraph("res/ui/off/title_off_4.png");
	_cg["off_credit"]   = ResourceServer::LoadGraph("res/ui/off/title_off_5.png");
	_cg["off_end"]      = ResourceServer::LoadGraph("res/ui/off/title_off_6.png");

	_menuPos = MENU::START;

	return true;
}

bool ModeTitle::Terminate() {
	base::Terminate();
	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	int menuNum = _cg.size() / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;

	if (trg & PAD_INPUT_DOWN) {
		_menuPos++;
	}
	if (trg & PAD_INPUT_UP) {
		_menuPos--;
	}
	if (trg & PAD_INPUT_B)	{

		if (_menuPos == 0) {
			// ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
			ModeServer::GetInstance()->Del(this);
			// ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
			ModeServer::GetInstance()->Add(new ModePlugin(), 1, "plugin");
		}
		if (_menuPos == 1) {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeTutorial(), 1, "tutorial");
		}
		if (_menuPos == 2) {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeRanking(), 1, "ranking");
		}
//		if (_menuPos == 3) {
		//	ModeServer::GetInstance()->Del(this);
//			ModeServer::GetInstance()->Add(new ModeOption(), 2, "option");
//		}
		if (_menuPos == 3) {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeCredit(), 1, "credit");
		}
		if (_menuPos == 4) {
			ModeServer::GetInstance()->Del(this);
			ApplicationBase::GetInstance()->Terminate();
		}
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _cgtitle, TRUE);

	DrawGraph(120, 480, _cg["off_start"], TRUE);
	DrawGraph(435, 575, _cg["off_tutorial"], TRUE);
	DrawGraph(120, 670, _cg["off_ranking"], TRUE);
//	DrawGraph(435, 765, _cg["off_option"], TRUE);
	DrawGraph(435, 765, _cg["off_credit"], TRUE);
	DrawGraph(120, 860, _cg["off_end"], TRUE);

	if (_menuPos == 0) { DrawGraph(120, 480, _cg["on_start"],    TRUE); }
	if (_menuPos == 1) { DrawGraph(435, 575, _cg["on_tutorial"], TRUE); }
	if (_menuPos == 2) { DrawGraph(120, 670, _cg["on_ranking"],  TRUE); }
//	if (_menuPos == 3) { DrawGraph(435, 765, _cg["on_option"],   TRUE); }
	if (_menuPos == 3) { DrawGraph(435, 765, _cg["on_credit"],   TRUE); }
	if (_menuPos == 4) { DrawGraph(120, 860, _cg["on_end"],      TRUE); }

	DrawFormatString(1500, 16, GetColor(255, 255, 255),"menuPos = %d",_menuPos);

	return true;
}
