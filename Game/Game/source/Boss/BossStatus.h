/**
 * @file   BossStatus.h
 * @brief  ボスステータスUI描画処理
 * 
 * @author matsuo tadahiko
 * @date   2021/02/25
 */

#pragma once

#include "appframe.h"

/**
 * @brief ボスステータスUI描画処理
 */
class BossStatus {
public:
	BossStatus();
	~BossStatus();

	/**
	 * @brief フレーム処理：描画
	 */
	void Render();

private:
	// 画像
	int _cgName;    // 名前
	int _cgFrame;   // ステータスのフレーム
	int _cgFrameBg; // ステータスのフレームの背面
	
	int _cgShield;  // シールドバー

	static const int HP_BAR_NUM = 5;  // HPバー本数
	const TCHAR* _hpBarString[HP_BAR_NUM] =  // HPバー画像ファイル名
	{ "res/ui/boss/enemy_hp_1.png","res/ui/boss/enemy_hp_2.png",
	  "res/ui/boss/enemy_hp_3.png","res/ui/boss/enemy_hp_4.png",
	  "res/ui/boss/enemy_hp_5.png" };

	const TCHAR* _iconString[HP_BAR_NUM] =  // HPバー画像ファイル名
	{ "res/ui/boss/enemy_hpicon_1.png","res/ui/boss/enemy_hpicon_2.png",
	  "res/ui/boss/enemy_hpicon_3.png","res/ui/boss/enemy_hpicon_4.png",
	  "res/ui/boss/enemy_hpicon_5.png" };

	int _cgHP[HP_BAR_NUM];    // HPバー
	int _cgIcon[HP_BAR_NUM];  // HPバー本数表示用

	const int ICON_POS_X[HP_BAR_NUM] =
	{ 1816,1784,1752,1720,1688 };
	const int ICON_POS_Y = 21;

	// 画像描画座標 定数定義
	const int FRAME_POS_X = 1090;  // ステータスバーのフレームX座標
	const int FRAME_POS_Y = 10;    // ステータスバーのフレームY座標
	const int FRAME_BG_POS_Y = 30; // ステータスバーの背景Y座標

	const int NAME_POS_X = 1650;  // ボス名X座標
	const int NAME_POS_Y = 130;   // ボス名Y座標

	const int HP_ONE = 1000;      // HPバー1本当たりのHP量
	const int HP_SIZE= 750;       // HPバー横幅
	const int HP_POS_X_L = 1113;  // HPバー左上X座標
	const int HP_POS_Y_L = 45;    // HPバー左上Y座標
	const int HP_POS_X_R = 1853;  // HPバー右下X座標
	const int HP_POS_Y_R = 80;    // HPバー右下Y座標

	const int SHIELD_ONE = 1000;     // シールドバー1本当たりのシールド量
	const int SHIELD_SIZE = 738;     // シールドバー横幅
	const int SHIELD_POS_X_L = 1124; // シールドバー左上X座標
	const int SHIELD_POS_Y_L = 90;   // シールドバー左上Y座標
	const int SHIELD_POS_X_R = 1862; // シールドバー右下X座標
	const int SHIELD_POS_Y_R = 120;  // シールドバー右下Y座標
};
