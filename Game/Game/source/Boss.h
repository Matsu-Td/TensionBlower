/**
 * @file   Boss.h
 * @brief  ボス関連処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#define  CHARA_DATA (modeGame->_charaData)

class Boss : public ObjectBase{
public:
	Boss();
	~Boss();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }

	void Initialize();
	void Process();
	void Render();

	/**
	 * @brief プレイヤーに弾き返された弾によるダメージ処理
     */
	void Damage();

	/**
	 * @brief プレイヤーから受けたダメージ量計算
	 */
	void AttackDamage();

	/**
	 * @brief フェーズ変更処理
	 */
	void FhaseChange();

	/**
	 * @brief 弾幕パターン切替処理
	 */
	void ShotPatternSwitch();

	/**
	 * @brief ダウン状態処理
	 */
	void StateDown();

	/**
	 * @brief 弾幕パターン1&2
	 */
	void ShotPattern1and2();

	/**
	 * @brief 弾幕パターン3
	 */
	void ShotPattern3();

	/**
	 * @brief 弾幕パターン4-1
	 */
	void ShotPattern4_1();

	/**
	 * @brief 弾幕パターン4-2
	 */
	void ShotPattern4_2();

	/**
     * @brief 弾幕パターン5
     */
	void ShotPattern5();

	/**
     * @brief 弾幕パターン6
     */
	void ShotPattern6();

	/**
	 * @brief 弾幕パターン7
	 */
	void ShotPattern7();

	/**
	 * @brief ヒットポイント値取得
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * @brief シールド値取得
	 */
	int GetShield() const { return _shield; }

	/**
	 * フェーズ数取得
	 */
	int GetPhase() const { return _phase; }

	static Boss* GetInstance() { return _pInstance; }

	static Boss* _pInstance;

	// プレイヤークラスで使用
	int _bulletNum;      // ダウン直前に出現していた弾の数カウント
	bool _mlsDownFlag;   // MLSで弾き返された弾でダウンすると「true」

private:
	int _hitpoint;       // ヒットポイント値
	int _shield;         // シールド値
	int _downTime;       // ダウン時間
	bool _stateDown;     // ダウン状態か(true:ダウン状態)

	int _shotCnt;        // 弾幕発射タイミングカウント
	int _mlsCnt;         // マルチロックオンシステム発動時のカウント
	int _reverseCnt;     // 弾幕回転方向が反転するカウント
	float _shotAngle;    // 弾幕の発射角度
	float _shotAngle1;   // 弾幕の発射角度
	float _setRotAngle;  // 発射一定角度セット
	float shotInterval;  // 弾幕の発射間隔
	int _shotPattern;    // 弾幕パターン3種ランダムで切替
	int _phase;          // フェーズ：HP残量で変化
	float _shotHeight;   // 弾幕を発射する高さ

	int  _gameClearCnt;  // クリアカウント
	bool _gameClearFlag; // クリアフラグ

	static constexpr float SHOT_DISTANCE = 10.0f;  // 弾幕を発生させる位置(ボス中心からの距離)
	static constexpr float ADD_POS_Y     = 8.5f;   // 当たり判定用Y座標加算値
	static constexpr float ROT_SPD       = 0.01f;  // ボスの向き回転用角速度

	static constexpr int PATTERN_CHANGE_CNT = 240; // 弾幕パターンを変化させるカウント最大値
	static constexpr int SHOT_REVERSE_CNT = 90;    // 弾幕回転方向を変化させるカウント最大値
	static constexpr int PHASE_ONE_HP   = 4000;    // フェーズ1へ移行する残りHP量
	static constexpr int PHASE_TWO_HP   = 3000;    // フェーズ2へ移行する残りHP量
	static constexpr int PHASE_THREE_HP = 2000;    // フェーズ3へ移行する残りHP量
	static constexpr int PHASE_FOUR_HP  = 1000;    // フェーズ4へ移行する残りHP量
	static constexpr int MIN_DOWN_TIME = 180;      // ダウン時間最小値(ダウン時間計算用)
	

	enum STATE {
		NORMAL,
		DOWN,
		RETURN,
		DEAD,
	};
	STATE _state;
};
