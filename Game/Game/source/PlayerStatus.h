/**
 * @file   PlayerStatus.h
 * @brief  プレイヤーステータスUI描画
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"

class PlayerStatus {
public:
	PlayerStatus();
	~PlayerStatus();

	/**
	 * @brief フレーム処理：描画
	 */
	void Render();

private:
	// 画像
	int _cgName;       // 名前    
	int _cgFrame;      // ステータスのフレーム
	int _cgFrameBg;    // ステータスのフレームの背景
	int _cgBarHP;      // HPバー
	int _cgBarEnergy;  // エネルギーバー


	// 画像描画座標　定数定義
	static constexpr int STATUS_FRAME_POS = 30; // ステータスバー座標
	static constexpr int HP_BAR_SIZE = 740;     // HPバー横幅サイズ
	static constexpr int ENERGY_BAR_SIZE = 738; // エネルギーバー横幅サイズ

	static constexpr int HP_POS_X_L = 68;       // HPバー左上X座標
	static constexpr int HP_POS_Y_L = 45;       // HPバー左上Y座標
	static constexpr int HP_POS_Y_R = 80;       // HPバー右下Y座標

	static constexpr int ENERGY_POS_X_L = 59;   // エネルギーバー左上X座標
	static constexpr int ENERGY_POS_Y_L = 90;   // エネルギーバー左上Y座標
	static constexpr int ENERGY_POS_Y_R = 120;  // エネルギーバー右下Y座標

	static constexpr int NUM_FRAME_POS_X = 30;  // 装弾数フレームX座標
	static constexpr int NUM_FRAME_POS_Y = 900; // 装弾数フレームY座標

	static constexpr int NAME_POS_X = 0;   // プレイヤー名X座標
	static constexpr int NAME_POS_Y = 130; // プレイヤー名Y座標
};