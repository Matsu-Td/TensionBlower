/**
 * @file   ModePause.cpp
 * @brief  ポーズモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "ModePause.h"
#include "ModeTitle.h"
#include "../Sound/Sound.h"

/*
 * 初期化
 */
bool ModePause::Initialize(){
	if (!base::Initialize()) { return false; }

	_cg = ResourceServer::LoadGraph("res/pause.png");

	_ui[0] = ResourceServer::LoadGraph("res/ui/pause/pause_on_01.png");
	_ui[1] = ResourceServer::LoadGraph("res/ui/pause/pause_on_02.png");
	_ui[2] = ResourceServer::LoadGraph("res/ui/pause/pause_off_01.png");
	_ui[3] = ResourceServer::LoadGraph("res/ui/pause/pause_off_02.png");

	_menuPos = 0;

	return true;
}

/*
 * 解放
 */
bool ModePause::Terminate(){
	base::Terminate();

	return true;
}

/*
 * フレーム処理：計算
 */
bool ModePause::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer(); 

	// ゲームパッドの上下キー及び左アナログスティック上下でメニュー選択
	if (_menuPos == 0) {
		if (trg & PAD_INPUT_DOWN) {
			PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
			_menuPos++;
		}

		// ゲームパッド「B」ボタンでポーズモード削除⇒ゲームモードへ戻る
		if (trg & PAD_INPUT_2) { 
			PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
			ModeServer::GetInstance()->Del(this);
		}
	}
	if (_menuPos == 1) {
		if (trg & PAD_INPUT_UP) {
			PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
			_menuPos--;
		}

		// ゲームパッド「B」ボタンでポーズモードとゲームモードを削除し、
		// タイトルモード追加
		if (trg & PAD_INPUT_2) {  
			PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
			StopSoundMem(gSound._bgm["boss"]);
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

			ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
		}
	}

	// ゲームパッド「START」ボタンでポーズモード削除⇒ゲームモードへ戻る
	if (trg & PAD_INPUT_8) { 
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

/*
 * フレーム処理：描画
 */
bool ModePause::Render(){
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