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
	/**
	 * @brief  初期化
	 * @return 処理の成否
	 */
	virtual bool Initialize();

	/**
	 * @brief  解放
	 * @return 処理の成否
	 */
	virtual bool Terminate();

	/**
	 * @brief  フレーム処理：計算
	 * @return 処理の成否
	 */
	virtual bool Process();

	/**
	 * @brief  フレーム処理：描画
	 * @return 処理の成否
	 */
	virtual bool Render();

protected:
	int _bg;      // 背景
	int _cg;      // 画像
	int _mode;    // フェード制御モード
	int _fadeCnt; // フェードカウント 
	int _dispCnt; // 表示カウント
	int _alpha;   // 画像のα値

	static constexpr int MAX_ALPHA = 255;    // 画像α値の最大値
	static constexpr int MAX_FADE_CNT = 30;  // フェードカウント最大値
	static constexpr int MAX_DISP_CNT = 90;  // 描画カウント最大値
	static constexpr int LOGO_POS_X = 460;   // ロゴ画像X座標
	static constexpr int LOGO_POS_Y = 425;   // ロゴ画像Y座標
};