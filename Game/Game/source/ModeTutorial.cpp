/**
 * @file   ModeTutorial.cpp
 * @brief  チュートリアル画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeTutorial.h"
#include "Sound.h"

/**
 * 初期化
 */
bool ModeTutorial::Initialize() {
	if (!base::Initialize()) { return false; }

	_bg    = ResourceServer::LoadGraph("res/title_back.png");
	_cg[0] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei1.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei2.png");
	_cg[2] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei3.png");
	_cg[3] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei4.png");
	_cg[4] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei5.png");
	_cg[5] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei6.png");
	_cg[6] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei7.png");
	_cg[7] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei8.png");
	_cg[8] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei9.png");

	// メニューUI画像読み込み(選択状:ON)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOn[i] = ResourceServer::LoadGraph(_fileNameOn[i]);
	}

	// メニューUI画像読み込み(未選択状態:OFF)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOff[i] = ResourceServer::LoadGraph(_fileNameOff[i]);
	}

	_menuPos = 0;

	return true;
}

/**
 * 解放
 */
bool ModeTutorial::Terminate() {
	base::Terminate();

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeTutorial::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	int menuNum = ALL_MENU_NUM / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;


	// ゲームパッドの上下キー及び左アナログスティック上下でメニュー選択
	if (trg & PAD_INPUT_DOWN) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos++;
	}
	if (trg & PAD_INPUT_UP) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos--;
	}

	// ゲームパッド「A」ボタンで「戻る」を選択するとチュートリアルモードを削除し、タイトルモード追加
	if (_menuPos == 9) { 
		if (trg & PAD_INPUT_2) {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
		}
	}

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeTutorial::Render() {
	base::Render();

	DrawGraph(0, 0, _bg, TRUE);
	DrawGraph(50, 50, _cg[_menuPos], TRUE);

	// メニューUI画像(未選択状態:OFF)は選択中は表示しない
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos != menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y[menuNum], _uiOff[menuNum], TRUE); }
	}

	// メニューUI画像(選択状態:ON)は選択中のみ表示する
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos == menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y[menuNum], _uiOn[menuNum], TRUE); }
	}

	return true;
}
