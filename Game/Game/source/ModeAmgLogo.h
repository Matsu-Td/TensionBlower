/**
 * @file   ModeAmgLogo.h
 * @brief  AMGロゴ表示
 * 
 * @author matsuo tadahiko
 * @date   2021/03/07
 */

#pragma once
#include "appframe.h"

class ModeAmgLogo :public ModeBase {
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _bg;      // 背景
	int _cg;      // 画像
	int _mode;    // フェード制御モード
	int _fadeCnt; // フェードカウント 
	int _dispCnt; // 表示カウント
	int _alpha;   // 画像のα値

	static constexpr int MAX_ALPHA = 255;
	static constexpr int MAX_FADE_CNT = 30;
	static constexpr int MAX_DISP_CNT = 90;
	static constexpr int LOGO_POS_X = 460;
	static constexpr int LOGO_POS_Y = 425;
};