#pragma once

/**
 * @file  BossStatus.h
 * @brief ボスステータスUI描画
 *
 * @date 2021-02-25
 */

#include "appframe.h"

class BossStatus {
public:
	BossStatus();
	~BossStatus();

	void Render();

private:
	// 画像
	int _cgName;    // 名前
	int _cgFrame;   // ステータスのフレーム
	int _cgFrameBg; // ステータスのフレームの背面
	int _cgHP[5];   // HPバー
	int _cgShield;  // シールドバー

	static constexpr int HP_BAR_NUM = 5;  // HPバー本数
	const TCHAR* _cgString[HP_BAR_NUM] =  // HPバー画像ファイル名
	{ "res/ui/boss/enemy_hp_1.png","res/ui/boss/enemy_hp_2.png",
	  "res/ui/boss/enemy_hp_3.png","res/ui/boss/enemy_hp_4.png",
	  "res/ui/boss/enemy_hp_5.png" };

	// 画像描画座標 定数定義
	static constexpr int FRAME_POS_X = 1090; // ステータスバーのフレームX座標
	static constexpr int FRAME_POS_Y = 30;   // ステータスバーのフレームY座標

	static constexpr int NAME_POS_X = 1650;  // ボス名X座標
	static constexpr int NAME_POS_Y = 130;   // ボス名Y座標

	static constexpr int HP_ONE = 1000;      // HPバー1本当たりのHP量
	static constexpr int HP_SIZE= 750;       // HPバー横幅
	static constexpr int HP_POS_X_L = 1113;  // HPバー左上X座標
	static constexpr int HP_POS_Y_L = 45;    // HPバー左上Y座標
	static constexpr int HP_POS_X_R = 1853;  // HPバー右下X座標
	static constexpr int HP_POS_Y_R = 80;    // HPバー右下Y座標

	static constexpr int SHIELD_ONE = 1000;     // シールドバー1本当たりのシールド量
	static constexpr int SHIELD_SIZE = 738;     // シールドバー横幅
	static constexpr int SHIELD_POS_X_L = 1124; // シールドバー左上X座標
	static constexpr int SHIELD_POS_Y_L = 90;   // シールドバー左上Y座標
	static constexpr int SHIELD_POS_X_R = 1862; // シールドバー右下X座標
	static constexpr int SHIELD_POS_Y_R = 120;  // シールドバー右下Y座標
};
