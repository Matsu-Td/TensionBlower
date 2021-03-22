/**
 * @file   Boss.h
 * @brief  ボス関連処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"
#define  CHARA_DATA (modeGame->_charaData)

class ShotPattern;
class BossDamage;

class Boss : public ObjectBase{
	friend ShotPattern;
	friend BossDamage;
public:
	Boss();
	~Boss();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }

	/**
	 * @brief 初期化
	 */
	void Initialize();

	/**
	 * @brief フレーム処理：計算
	 */
	void Process();

	/**
	 * @brief フレーム処理：描画
	 */
	void Render();

	/**
	 * @brief フェーズ変更処理
	 */
	void FhaseChange();

	/**
	 * @brief ダウン状態処理
	 */
	void StateDown();

	/**
	 * @brief 6種類の声データをランダムで流す
	 */
	void PlayAttackVoiceChange();

	/**
	 * @brief 声データ再生
	 * @param voiceName 声データの名前
	 */
	void PlayVoice(std::string voiceName);

	/**
	 * @brief ヒットポイント値取得
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * @brief シールド値取得
	 */
	int GetShield() const { return _shield; }

	/**
	 * @brief フェーズ数取得
	 */
	int GetPhase() const { return _phase; }

	/**
	 * @brief 死亡処理
	 */
	void Dead();

	static Boss* GetInstance() { return _pInstance; }

	static Boss* _pInstance;

	// プレイヤークラスで使用
	int _bulletNum;      // ダウン直前に出現していた弾の数カウント
	bool _mlsDownFlag;   // MLSで弾き返された弾でダウンすると「true」

	// 状態
	enum class STATE {
		NORMAL,  // 通常
		DOWN,    // ダウン
		RETURN,  // 復帰
		DEAD,    // 死亡、破壊
	};
	STATE GetState() const { return _state; };

private:
	int  _hitpoint;      // ヒットポイント値
	int  _shield;        // シールド値
	int  _downTime;      // ダウン時間
	bool _stateDown;     // ダウン状態か(true:ダウン状態)

	int   _shotCnt;      // 弾幕発射タイミングカウント
	int   _mlsCnt;       // マルチロックオンシステム発動時のカウント
	int   _reverseCnt;   // 弾幕回転方向が反転するカウント
	float _shotAngle;    // 弾幕の発射角度
	float _shotAngle1;   // 弾幕の発射角度
	float _setRotAngle;  // 発射一定角度セット
	int   _shotPattern;  // 弾幕パターン3種ランダムで切替
	int   _phase;        // フェーズ：HP残量で変化
	float _shotHeight;   // 弾幕を発射する高さ
	float _laserAngle;   // レーザーの発射角度

	int  _deadCnt;  // 死亡カウント
	bool _deadFlag; // 死亡フラグ

	static constexpr int ATTACK_VOICE_NUM = 6;     // 攻撃時の声データ総数
	std::string _attackNameNo[ATTACK_VOICE_NUM] =  // 攻撃時の声データの名前を格納
	{ "attack1","attack1" ,"attack2" ,"attack4" ,"attack5" ,"attack6" };


	static constexpr float ADD_POS_Y     = 9.0f;   // 当たり判定用Y座標加算値
	static constexpr float ROT_SPD       = 0.01f;  // ボスの向き回転用角速度

	static constexpr int PHASE_ONE_HP   = 4000;    // フェーズ1へ移行する残りHP量
	static constexpr int PHASE_TWO_HP   = 3000;    // フェーズ2へ移行する残りHP量
	static constexpr int PHASE_THREE_HP = 2000;    // フェーズ3へ移行する残りHP量
	static constexpr int PHASE_FOUR_HP  = 1000;    // フェーズ4へ移行する残りHP量
	static constexpr int MIN_DOWN_TIME = 180;      // ダウン時間最小値(ダウン時間計算用)

	STATE _state;  // 状態

	std::unique_ptr<ShotPattern> _patternCall;
	std::unique_ptr<BossDamage> _damageCall;
};

#include "ShotPattern.h"
#include "BossDamage.h"
