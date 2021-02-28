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

	void Render();

private:
	// 画像
	int _cgName;       // 名前    
	int _cgFrame;      // ステータスのフレーム
	int _cgFrameBg;    // ステータスのフレームの背景
	int _cgBarHP;      // HPバー
	int _cgBarEnergy;  // エネルギーバー
	int _cgRemainFrame;// 装弾数表示フレーム

	static constexpr int ALL_NUM = 10; // 数字の数(0～9)
	int _cgRemainNum[ALL_NUM];         // 装弾数表示用数字画像格納

	const TCHAR* _numString[ALL_NUM]=  // 数字ファイル名
	{"res/ui/player/remain_0.png", "res/ui/player/remain_1.png", 
	 "res/ui/player/remain_2.png", "res/ui/player/remain_3.png", 
	 "res/ui/player/remain_4.png", "res/ui/player/remain_5.png",
	 "res/ui/player/remain_6.png", "res/ui/player/remain_7.png", 
	 "res/ui/player/remain_8.png", "res/ui/player/remain_9.png" };

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

	static constexpr int NUM_POS_X1 = 45;  // 装弾数用数字のX座標(100の位)
	static constexpr int NUM_POS_X2 = 100; // 装弾数用数字のX座標(10の位)
	static constexpr int NUM_POS_X3 = 155; // 装弾数用数字のX座標(1の位)
	static constexpr int NUM_POS_Y = 920;  // 装弾数用数字のY座標(共通)
};