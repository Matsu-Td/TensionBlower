#pragma once

/**
 * @file  Boss.h
 * @brief ボス関連処理
 *
 * @date 2021-02-11
 */

#include "appframe.h"
#include "BossBullet.h"
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
	 * プレイヤーに弾き返された弾によるダメージ処理
     */
	void Damage();

	/**
	 * プレイヤーから受けたダメージ量計算
	 */
	void AttackDamage();

	/**
	 * フェーズ変更処理
	 */
	void FhaseChange();

	/**
	 * 弾幕パターン切替処理
	 */
	void ShotPatternSwitch();

	/**
	 * ダウン状態処理
	 */
	void StateDown();

	/**
	 * 弾幕パターン1&2
	 */
	void ShotPattern1and2();

	/**
	 * 弾幕パターン3
	 */
	void ShotPattern3();

	/**
	 * 弾幕パターン4-1
	 */
	void ShotPattern4_1();

	/**
	 * 弾幕パターン4-2
	 */
	void ShotPattern4_2();

	/**
     * 弾幕パターン5
     */
	void ShotPattern5();

	/**
     * 弾幕パターン6
     */
	void ShotPattern6();

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
	float _setRotAngle;  
	float shotInterval;  // 弾幕の発射間隔
	int _shotPattern;    // 弾幕パターン3種ランダムで切替
	int _phase;          // フェーズ：HP残量で変化
	float _height;       // 弾幕を発射する高さ
	float _upDown;       // 弾幕の発射高さ変化用


	int _gameClearCnt;      // クリアカウント
	bool _gameClearFlag;    // クリアフラグ

	float _a;        // デバッグ確認用

	static constexpr float SHOT_DISTANCE = 10.0f;  // 弾幕を発生させる位置(ボス中心からの距離)
	
	static constexpr int PATTERN_CHANGE_CNT = 240; // 弾幕パターンを変化させるカウント最大値
	static constexpr int SHOT_REVERSE_CNT = 90;    // 弾幕回転方向を変化させるカウント最大値
	static constexpr int PHASE_ONE_HP   = 4000;    // フェーズ1へ移行する残りHP量
	static constexpr int PHASE_TWO_HP   = 3000;    // フェーズ2へ移行する残りHP量
	static constexpr int PHASE_THREE_HP = 2000;    // フェーズ3へ移行する残りHP量
	static constexpr int PHASE_FOUR_HP  = 1000;    // フェーズ4へ移行する残りHP量
	static constexpr int MIN_DOWN_TIME = 180;      // ダウン時間最小値(ダウン時間計算用)
	static constexpr int DOWN_TIME_ONE_BULLET = 90;      // ダウン時間最小値(ダウン時間計算用)
};
