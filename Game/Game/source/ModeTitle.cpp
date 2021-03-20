/**
 * @file   ModeTitle.cpp
 * @brief  タイトル画面
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGameStart.h"
#include "ModeCredit.h"
#include "ModeTutorial.h"
#include "ModeRanking.h"
#include "ModeGame.h"
#include "TitleBGM.h"
#include "Sound.h"
#include "PlayerVoice.h"
#include "BossVoice.h"

/**
 * 初期化
 */
bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	// BGM再生(再生していない時)
	if (!CheckSoundMem(gSound._bgm["titlebgm"])) {
		ModeServer::GetInstance()->Add(NEW TitleBGM(), 0, "titlebgm");
	}

	// プレイヤーorボスの声でタイトルコールする(ランダム)
	int voice = rand() % 2;
	if (voice == 0) {
		// プレイヤー
		PlaySoundMem(gPlayerVoice._vc["title"], DX_PLAYTYPE_BACK);
	}
	else {
		// ボス
		PlaySoundMem(gBossVoice._vc["title"], DX_PLAYTYPE_BACK);
	}

	_bg      = ResourceServer::LoadGraph("res/title_back.png");
	_cgtitle = ResourceServer::LoadGraph("res/logo_title.png");

	// メニューUI画像読み込み(選択状:ON)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOn[i] = ResourceServer::LoadGraph(_fileNameOn[i]);
	}

	// メニューUI画像読み込み(未選択状態:OFF)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOff[i] = ResourceServer::LoadGraph(_fileNameOff[i]);
	}
	
	_menuPos = MENU::START;  // 初期位置

	return true;
}

/**
 * 解放
 */
bool ModeTitle::Terminate() {
	base::Terminate();

	return true;
}

/**
 * タイトルメニュー選択
 */
void ModeTitle::MenuSelect() {

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ゲームパッドの上下キー及び左アナログスティック上下でメニュー選択
	if (trg & PAD_INPUT_RIGHT) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos++;
	}
	if (trg & PAD_INPUT_LEFT) {
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos--;
	}

	if (trg & PAD_INPUT_2) {
		PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
		switch (_menuPos) {
		case MENU::START:
			// BGM再生停止
			StopSoundMem(gSound._bgm["titlebgm"]);
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("titlebgm"));
			ModeChange(NEW ModeGame(),   1, "game");   
			break;
		case MENU::TUTORIAL:
			ModeChange(NEW ModeTutorial(), 1, "tutorial"); break;

		case MENU::CREDIT:
			ModeChange(NEW ModeCredit(),   1, "credit");   break;

		case MENU::GAME_END: 
			ModeServer::GetInstance()->Del(this);
			ApplicationBase::GetInstance()->GameEnd();
			break;
		}
	}
}

/**
 * タイトル削除、次のモード登録
 */
void ModeTitle::ModeChange(ModeBase* nextMode, int layer, const char* modeName) {
	// タイトルモードを削除
	ModeServer::GetInstance()->Del(this);
	// 次のモードを登録
	ModeServer::GetInstance()->Add(nextMode, layer, modeName);
}

/**
 * フレーム処理：計算
 */
bool ModeTitle::Process() {
	base::Process();

	int menuNum = ALL_MENU_NUM / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;

	MenuSelect();

	return true;
}

/**
 * フレーム処理：描画
 */
bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _bg, TRUE);
	DrawGraph(0, 0, _cgtitle, TRUE);

	// メニューUI画像(未選択状態:OFF)は選択中は表示しない
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos != menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y, _uiOff[menuNum], TRUE); }
	}

	// メニューUI画像(選択状態:ON)は選択中のみ表示する
	for (int menuNum = 0; menuNum < MENU_NUM; menuNum++) {
		if (_menuPos == menuNum) { DrawGraph(MENU_POS_X[menuNum], MENU_POS_Y, _uiOn[menuNum], TRUE); }
	}

	return true;
}
