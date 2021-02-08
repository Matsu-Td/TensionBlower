#pragma once

/**
 * @file  CharaData.h
 * @brief キャラデータ(プレイヤー、ボス)JSONファイル読み込み処理
 * 
 * @date 2021-02-08
 */

#include "appframe.h"

class CharaData{
public:
	CharaData(std::string filePath, std::string fileName);
	~CharaData();

	/**
	* プレイヤーデータ
	*/
	int _maxHP;         // 最大HP
	int _maxEnergy;     // 最大エネルギー
	float _mvSpdNorm;   // 移動速度(通常状態)
	float _mvSpdChrg;   // 移動速度(溜め状態)  
	float _mvSpdDash;   // 移動速度(ダッシュ状態)

	int _egJump;        // エネルギー消費量：ジャンプ
	int _egDash;        // エネルギー消費量：ダッシュ
	int _egMLS;         // エネルギー消費量：マルチロックシステム
	int _egAtck1;       // エネルギー消費量：強近接攻撃1
	int _egAtck2;       // エネルギー消費量：強近接攻撃2
	int _egAtck3;       // エネルギー消費量：強近接攻撃3
	int _egAtck4;       // エネルギー消費量：強近接攻撃4

	int _egAutoRec;     // エネルギー回復量：自動回復
	float _egAutoXChrg; // エネルギー回復量：溜め行動
	int _egAutoXArea;   // エネルギー回復量：ボス付近での行動
	int _egAvoid;       // エネルギー回復量：ボスの弾カスリ判定
	int _egShotNum;     // エネルギー回復量：ボスダウン時の吸収した弾1つ当たり

	int _wkDmgHP1;      // HPダメージ量(シールド有)：弱近接攻撃1
	int _wkDmgHP2;      // HPダメージ量(シールド有)：弱近接攻撃2
	int _wkDmgHP3;      // HPダメージ量(シールド有)：弱近接攻撃3
	int _wkDmgHP4;      // HPダメージ量(シールド有)：弱近接攻撃4
	int _stDmgHP1;      // HPダメージ量(シールド有)：強近接攻撃1
	int _stDmgHP2;      // HPダメージ量(シールド有)：強近接攻撃2
	int _stDmgHP3;      // HPダメージ量(シールド有)：強近接攻撃3
	int _stDmgHP4;      // HPダメージ量(シールド有)：強近接攻撃4
	int _shotDmgHP;     // HPダメージ量(シールド有)：射撃攻撃 
	int _repelDmgHP;    // HPダメージ量(シールド有)：弾き返し

	int _wkDmgSld1;     // シールドダメージ量：弱近接攻撃1
	int _wkDmgSld2;     // シールドダメージ量：弱近接攻撃2
	int _wkDmgSld3;     // シールドダメージ量：弱近接攻撃3
	int _wkDmgSld4;     // シールドダメージ量：弱近接攻撃4
	int _stDmgSld1;     // シールドダメージ量：強近接攻撃1
	int _stDmgSld2;     // シールドダメージ量：強近接攻撃2
	int _stDmgSld3;     // シールドダメージ量：強近接攻撃3
	int _stDmgSld4;     // シールドダメージ量：強近接攻撃4
	int _shotDmgSld;    // シールドダメージ量：射撃攻撃
	int _repelDmgSld;   // シールドダメージ量：弾き返し

	int _wkDmg1;        // HPダメージ量(シールド無)：弱近接攻撃1
	int _wkDmg2;        // HPダメージ量(シールド無)：弱近接攻撃2
	int _wkDmg3;        // HPダメージ量(シールド無)：弱近接攻撃3
	int _wkDmg4;        // HPダメージ量(シールド無)：弱近接攻撃4
	int _stDmg1;        // HPダメージ量(シールド無)：強近接攻撃1
	int _stDmg2;        // HPダメージ量(シールド無)：強近接攻撃2
	int _stDmg3;        // HPダメージ量(シールド無)：強近接攻撃3
	int _stDmg4;        // HPダメージ量(シールド無)：強近接攻撃4
	int _shotDmg;       // HPダメージ量(シールド無)：射撃攻撃
	int _repelDmg;      // HPダメージ量(シールド無)：弾き返し

	/**
	* ボスデータ
	*/
	struct BOSS {
		int maxHP;       // 最大HP
		int maxShield;   // 最大シールド値
		int shotDmg;     // ダメージ量：弾幕(弾1つあたり)
		int exolosionDmg;// ダメージ量：誘爆
		int laserDmg;    // ダメージ量：レーザー
	};
	BOSS _boss;

private:
	std::string StringFileLoad(std::string fileName);
	int JsonLoad(std::string filePath, std::string fileName);
};
