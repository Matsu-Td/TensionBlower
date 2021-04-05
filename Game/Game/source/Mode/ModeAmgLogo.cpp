/**
 * @file   ModeAmgLogo.cpp
 * @brief  AMGロゴ描画処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#include "ModeAmgLogo.h"
#include "ModeTeamLogo.h"

/*
 * 初期化 
 */
bool ModeAmgLogo::Initialize() {
	if (!base::Initialize()) { return false; }

	_bg = ResourceServer::LoadGraph("res/logo_bg.png");
	_cg = ResourceServer::LoadGraph("res/amg_logo.png");

	_alpha = 0;
	_fadeCnt = 0;
	_dispCnt = MAX_DISP_CNT;
	_mode = 0;

	return true;
}

/*
 * 解放 
 */
bool ModeAmgLogo::Terminate() {
	base::Terminate();

	return true;
}

/*
 * フレーム処理：計算
 */
bool ModeAmgLogo::Process() {
	base::Process();

	// フェードイン
	if (_mode == 0) {
		_fadeCnt++;
		if (_fadeCnt >= MAX_FADE_CNT) {
			_fadeCnt = MAX_FADE_CNT;
			_mode = 1;
		}
	}

	// 表示したまま停止
	if (_mode == 1) {
		_dispCnt--;
		if (_dispCnt <= 0) {
			_mode = 2;
		}
	}

	// フェードアウト
	if (_mode == 2) {
		_fadeCnt--;
		if (_fadeCnt <= 0) {
			_fadeCnt = 0;
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(NEW ModeTeamLogo(), 1, "teamlogo");
		}
	}

	// 画像α値計算
	_alpha = MAX_ALPHA * _fadeCnt / MAX_FADE_CNT;

	return true;
}

/*
 * フレーム処理：描画
 */
bool ModeAmgLogo::Render() {
	base::Render();

	DrawGraph(0, 0, _bg, FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	DrawGraph(LOGO_POS_X, LOGO_POS_Y, _cg, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return true;
}
