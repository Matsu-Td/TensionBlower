#pragma once

/**
 * @file  Player.h
 * @brief プレイヤー関連処理
 *
 * @date 2021-02-08
 */

#include "appframe.h"
#include "PlayerBullet.h"
#include "BulletServer.h"
#define  CHARA_DATA (modeGame->_charaData)

class PlayerAttack;

class Player : public ObjectBase{
	friend PlayerAttack;
public:
	Player();
	~Player();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	void Initialize();
	void Process();
	void Render();

	void ShortDash();
	void NormDash();
	void Charge();

	/**
	 * 消費エネルギー処理
	 * @param costEnergy 消費エネルギー量
	 */
	void CostEnergy(float costEnergy);

	/**
     * 当たり判定
     */
	void Collision();

	/**
	 * ジャンプ処理
	 */
	void JumpAction();

	/**
     * 射撃攻撃 :ゲームパッドRTで射撃
     * @param rt ゲームパッド「RT」入力値
     */
	void ShotAttack(float rt);

	/**
	* カメラロック中の移動、ダッシュモーション切替処理／
	* 左アナログスティックの倒した角度によってキャラの状態、モーションを遷移
	* @param length  := sqrt(lx * lx + ly * ly) 左アナログスティックの入力値
	*/
	void LeftAnalogDeg(float length);

	/**
	 * エネルギー量取得
	 * @return プレイヤーの現在のエネルギー量を取得
	 */
	int GetEnergy() { return _energy; }

	/**
     * 近接攻撃：シールド状態のボスのHPに与えるダメージ量取得
     * @return プレイヤーの現在の近接攻撃ダメージ量
     */
	int GetNowDmgHP()   const { return _nowDmgHP; }

	/**
	 * 近接攻撃：シールド状態のボスのシールドに与えるダメージ量取得
	 * @return プレイヤーの現在の近接攻撃ダメージ量
	 */
	int GetNowDmgSld()  const { return _nowDmgSld; }

	/**
	 * 近接攻撃：通常状態のボスのHPに与えるダメージ量取得
	 * @return プレイヤーの現在の近接攻撃ダメージ量
	 */
	int GetNowDmgNorm() const { return _nowDmgNorm; }

	/**
	 * プレイヤーインスタンスアクセス用
	 * @return _pInstance プレイヤークラスポインタ
	 */
	static Player* GetInstance() { return _pInstance; }
	static Player* _pInstance;

	static constexpr float GROUND_Y = 0.0f;  // 地上のY座標

protected:


	// ステータス関連
	int _hitpoint;       // ヒットポイント値
	int _energy;         // エネルギー値
	int _nowDmgHP;       // 現在の近接攻撃の種類(ボスへのダメージ用)
	int _nowDmgSld;      // 現在の近接攻撃の種類(ボスへのダメージ用)
	int _nowDmgNorm;     // 現在の近接攻撃の種類(ボスへのダメージ用)
	int _bulletNum;      // 弾の残弾数

	// ジャンプ関連
	bool _isCanJump;     // ジャンプ可否(true:可, false:不可)
	float  _jumpTime;    // ジャンプ時間制御

	// ダッシュ関連
	bool _isDash;        // ダッシュ開始(全種類)
	bool _isShortDash;   // 短押しダッシュ中か(true:ダッシュ中)
	bool _isCanLongDash; // 長押しダッシュ可否(true:可能, false:不可)
	int _shortDashTime;  // 短押しダッシュ移動時間

	// 射撃関連
	bool _canShotFlag;   // 射撃可否(true:可能, false:不可)
	bool _shotZeroFlag;  // 装弾数ゼロフラグ(true:装弾数「0」状態, false:装弾が「1」以上ある状態)
	int _shotInterval;   // 弾の発射間隔
	int _reloadTime;     // リロード開始までの時間
	bool _shotFlag;      // 射撃中か

	// エネルギー溜め行動関連
	bool _isCharging;    // エネルギー溜め中か(true:溜め中, false:溜め未実施)
	bool _atChargeFlag;  // エネルギー自動回復開始フラグ
	int _atChargeCnt;    // エネルギー自動回復開始インターバル

	// 近接攻撃関連
	bool _attackFlag;      // 攻撃発生フラグ(攻撃発動中)
	int _attackCnt;        // 攻撃遷移、終了カウント(攻撃モーション総再生時間を代入)
	int _attackReloadTime; // 近接攻撃用リロード時間(リロード中は近接攻撃不可)
	int _receptionTime;    // 次の近接攻撃遷移受付時間
	int _canHitFlag;       // 近接攻撃当たり判定可否(true:可能, false:不可)

	std::unordered_map<std::string, int> _attackTotalTime;  // 各攻撃モーションの総再生時間を格納する

	static constexpr int ATTACK_NUM = 8;  // 近接攻撃の種類の数
	std::string AttackName[ATTACK_NUM] =  // 各近接攻撃の名前を格納
	{ "weak_atck1" ,"weak_atck2" ,"weak_atck3" ,"weak_atck4", 
	  "strg_atck1", "strg_atck2", "strg_atck3", "strg_atck4" };

	// その他
	bool _nearPosFlag;   // ボスの近くにいるか(true:ボスの近くにいる)
	float _bsAngle;      // ボスの位置、角度
	int _lfAnalogDeg;    // 左アナログスティックの倒した方向(角度)
	int _gameOverCnt;    // プレイヤー死亡からゲームオーバーまでの時間
	bool _gameOverFlag;  // ゲームオーバーフラグ
	bool _camStateMLS;   // マルチロックオンシステム発動中か

	// プレイヤー状態(モーション)管理
	enum class STATE {
		NONE,            // 無し
		WAIT,            // 待機
		WALK,            // 通常移動
		FOR_DASH,        // 前方ダッシュ移動
		JUMP,            // ジャンプ
		LEFT_MOVE,       // 左方移動(カメラロック中のみ)
		RIGHT_MOVE,      // 右方移動(カメラロック中のみ)
		BACK_MOVE,       // 後方移動(カメラロック中のみ)
		LEFT_DASH,       // 左方ダッシュ移動(カメラロック中のみ)
		RIGHT_DASH,      // 右方ダッシュ移動(カメラロック中のみ)
		BACK_DASH,       // 後方ダッシュ移動(カメラロック中のみ)
		WEAK_ATCK1,      // 弱近接攻撃1
		WEAK_ATCK2,      // 弱近接攻撃2
		WEAK_ATCK3,      // 弱近接攻撃3
		WEAK_ATCK4,      // 弱近接攻撃4
		STRG_ATCK1,      // 強近接攻撃1
		STRG_ATCK2,      // 強近接攻撃2
		STRG_ATCK3,      // 強近接攻撃3
		STRG_ATCK4,      // 強近接攻撃4
		SHOT_ATCK,       // 射撃攻撃
	};
	STATE _state; // プレイヤーの状態

	/**
	 * エネルギー管理
	 * @param oldState 処理前のプレイヤーの状態
	 */
	void EnergyManager(STATE oldState);

	/**
	 * モデルモーション切替
	 * @param oldState 処理前のプレイヤーの状態
	 */
	void MortionSwitch(STATE oldState);

	static constexpr float GRAVITY       = 0.9f; // 重力加速度値
	static constexpr int SHORT_DASH_CNT  = 10;   // 短押しダッシュ時間
	static constexpr int MAX_BULLET      = 100;  // 最大装弾数
	static constexpr int AUTO_CHARGE_CNT = 120;  // 自動回復開始カウント
	static constexpr int RELOAD_TIME     = 90;   // 近接・射撃攻撃リロード時間

	static constexpr int ANALOG_REG_FOR   = 120; // 左アナログスティックを倒す前方向判定の角度範囲(ターゲットロック中のみ使用)
	static constexpr int ANALOG_REG_OTHER = 45;  // 左アナログスティックを倒す前方向以外の角度範囲(ターゲットロック中のみ使用)

	PlayerAttack* _attack;

	// デバッグ用
	float _len;          // デバッグ用（プレイヤーとボスの距離）
	bool _swCharge;      // デバッグ用(エネルギー消費ON/OFF切替)
};

#include "PlayerAttack.h"