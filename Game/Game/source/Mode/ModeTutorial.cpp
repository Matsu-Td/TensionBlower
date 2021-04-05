/**
 * @file   ModeTutorial.cpp
 * @brief  チュートリアルモードクラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeTutorial.h"
#include "../Sound/Sound.h"

/*
 * 初期化
 */
bool ModeTutorial::Initialize() {
	if (!base::Initialize()) { return false; }

	// 背景読み込み
	_bg    = ResourceServer::LoadGraph("res/title_back.png");

	// 画像読み込み
	_cg[0] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei11.png");
	_cg[1] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei12.png");
	_cg[2] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei1.png");
	_cg[3] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei2.png");
	_cg[4] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei3.png");
	_cg[5] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei5.png");
	_cg[6] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei7.png");
	_cg[7] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei8.png");
	_cg[8] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei9.png");
	_cg[9] = ResourceServer::LoadGraph("res/ui/tutorial/setsumei10.png");

	// 動画読み込み
	_movieHandle[2] = ResourceServer::LoadGraph("res/movie/move.mp4");
	_movieHandle[3] = ResourceServer::LoadGraph("res/movie/dash.mp4");
	_movieHandle[4] = ResourceServer::LoadGraph("res/movie/jump.mp4");
	_movieHandle[5] = ResourceServer::LoadGraph("res/movie/MLS.mp4");
	_movieHandle[6] = ResourceServer::LoadGraph("res/movie/lattack.mp4");
	_movieHandle[7] = ResourceServer::LoadGraph("res/movie/hattack.mp4");
	_movieHandle[8] = ResourceServer::LoadGraph("res/movie/charge.mp4");
	
	// メニューUI画像読み込み(選択状態:ON)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOn[i] = ResourceServer::LoadGraph(_fileNameOn[i]);
	}

	// メニューUI画像読み込み(未選択状態:OFF)
	for (int i = 0; i < MENU_NUM; i++) {
		_uiOff[i] = ResourceServer::LoadGraph(_fileNameOff[i]);
	}

	_menuPos = 0;
	
	// 動画の再生位置を最初にする
	SeekMovieToGraph(_movieHandle[_menuPos], 0);
	// 先頭の動画再生開始
	PlayMovieToGraph(_movieHandle[0]);

	return true;
}

/*
 * 解放
 */
bool ModeTutorial::Terminate() {
	base::Terminate();

	return true;
}

/*
 * フレーム処理：計算
 */
bool ModeTutorial::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	// 前のメニュー位置を保存
	_oldMenuPos = _menuPos;

	int menuNum = ALL_MENU_NUM / 2;
	_menuPos = (_menuPos + menuNum) % menuNum;


	// ゲームパッドの上下キー及び左アナログスティック上下でメニュー選択
	if (trg & PAD_INPUT_DOWN) {
		// 選択音再生
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos++;
	}
	if (trg & PAD_INPUT_UP) {
		// 選択音再生
		PlaySoundMem(gSound._se["select"], DX_PLAYTYPE_BACK);
		_menuPos--;
	}

	if (_menuPos != _oldMenuPos) {
		// 選択中の動画を再生
		SeekMovieToGraph(_movieHandle[_menuPos], 0);
		PlayMovieToGraph(_movieHandle[_menuPos]);
	}
	// 動画をループさせる
	// 動画が停止したら再生位置を最初に戻す
	else if (GetMovieStateToGraph(_movieHandle[_menuPos]) == 0) {
		SeekMovieToGraph(_movieHandle[_menuPos], 0);
		PlayMovieToGraph(_movieHandle[_menuPos]);
	}

	// ゲームパッド「A」ボタンで「戻る」を選択するとチュートリアルモードを削除し、タイトルモード追加
	if (_menuPos == 9) { 
		if (trg & PAD_INPUT_2) {
			// 決定音再生
			PlaySoundMem(gSound._se["decision"], DX_PLAYTYPE_BACK);
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "title");
		}
	}

	return true;
}

/*
 * フレーム処理：描画
 */
bool ModeTutorial::Render() {
	base::Render();

	DrawGraph(0, 0, _bg, TRUE);

	DrawGraph(SETSUMEI_POS, SETSUMEI_POS, _cg[_menuPos], TRUE);

	if (_menuPos < MENU_NUM) {
		DrawGraph(MOVIE_POS_X, MOVIE_POS_Y, _movieHandle[_menuPos], FALSE);
	}

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
