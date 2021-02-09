
/**
 * @file  ModeOption.cpp
 * @brief ポーズ画面
 *
 * @date 2021-02-08
 */

#include "ApplicationMain.h"
#include "ModeOption.h"
#include "ModeTitle.h"

/**
 * 初期化
 */
bool ModeOption::Initialize(){
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/仮素材/ポーズ.png");

	_ui[0] = ResourceServer::LoadGraph("res/ui/on/title_on_1.png");
	_ui[1] = ResourceServer::LoadGraph("res/ui/on/title_on_6.png");
	_ui[2] = ResourceServer::LoadGraph("res/ui/off/title_off_1.png");
	_ui[3] = ResourceServer::LoadGraph("res/ui/off/title_off_6.png");

	_menuPos = 0;

	return true;
}

/**
 * 解放
 */
bool ModeOption::Terminate(){
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeOption::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer(); 

	// ゲームパッドの上下キー及び左アナログスティック上下でメニュー選択
	if (_menuPos == 0) {
		if (trg & PAD_INPUT_DOWN) {
			_menuPos++;
		}

		// ゲームパッド「B」ボタンでポーズモード削除⇒ゲームモードへ戻る
		if (trg & PAD_INPUT_2) {  
			ModeServer::GetInstance()->Del(this);
		}
	}
	if (_menuPos == 1) {
		if (trg & PAD_INPUT_UP) {
			_menuPos--;
		}

		// ゲームパッド「B」ボタンでポーズモードとゲームモードを削除し、
		// タイトルモード追加
		if (trg & PAD_INPUT_2) {  
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

			ModeTitle* modeTitle = NEW ModeTitle();
			ModeServer::GetInstance()->Add(modeTitle, 1, "title");
		}
	}

	// ゲームパッド「START」ボタンでポーズモード削除⇒ゲームモードへ戻る
	if (trg & PAD_INPUT_8) { 
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeOption::Render(){
	base::Render();

	DrawGraph(0, 0, _cg, TRUE);

	// 仮実装
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