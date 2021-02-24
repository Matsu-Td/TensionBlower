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

// プレイヤークラスに関係するクラスの宣言
class PlayerAttack;
class PlayerMotion;
class PlayerEnergy;
class PlayerDash;
class PlayerShoot;
class PlayerJump;

class Player : public ObjectBase{
	friend PlayerAttack;
	friend PlayerMotion;
	friend PlayerEnergy;
	friend PlayerDash;
	friend PlayerShoot;
	friend PlayerJump;
public:
	Player();
	~Player();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	void Initialize();
	void Process();
	void Render();

	/**
     * 当たり判定
     */
	void Collision();

	/**
	 * HP値取得
	 * @return プレイヤーの現在のHP値を取得
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * エネルギー量取得
	 * @return プレイヤーの現在のエネルギー量を取得
	 */
	int GetEnergy() const { return _energy; }

	/**
	 * 弾の残弾数
	 * @return プレイヤーの現在の残弾数を取得
	 */
	int GetBulletNum() const { return _bulletNum; }

	/**
     * 近接攻撃：シールド状態のボスのHPに与えるダメージ量取得
     * @return プレイヤーの現在の近接攻撃ダメージ量
     */
	int GetNowDmgHP() const { return _nowDmgHP; }

	/**
	 * 近接攻撃：シールド状態のボスのシールドに与えるダメージ量取得
	 * @return プレイヤーの現在の近接攻撃ダメージ量
	 */
	int GetNowDmgSld() const { return _nowDmgSld; }

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
	// ステータス
	int _hitpoint;       // ヒットポイント値
	int _energy;         // エネルギー値

	// ジャンプ用
	float _jumpTime;     // ジャンプ時間制御
	bool  _canJump;      // ジャンプ可否(true:可, false:不可)

	// ダッシュ用
	int  _shortDashTime; // 短押しダッシュ移動時間
	bool _isDash;        // ダッシュ開始(全種類)
	bool _isShortDash;   // 短押しダッシュ中か(true:ダッシュ中)
	bool _canLongDash;   // 長押しダッシュ可否(true:可能, false:不可)

	// 射撃用
	int  _shotInterval;  // 弾の発射間隔
	int  _reloadTime;    // リロード開始までの時間
	int  _bulletNum;     // 弾の残弾数
	bool _canShot;       // 射撃可否(true:可能, false:不可)
	bool _isZeroShot;    // 装弾数ゼロフラグ(true:装弾数「0」状態, false:装弾が「1」以上ある状態)
	bool _isShooting;    // 射撃中か
	
	// エネルギー溜め用
	int  _autoChargeCnt; // エネルギー自動回復開始インターバル
	bool _isCharging;    // エネルギー溜め中か(true:溜め中, false:溜め未実施)
	bool _canAutoCharge; // エネルギー自動回復開始フラグ

	// 近接攻撃用
	int  _attackCnt;        // 攻撃遷移、終了カウント(攻撃モーション総再生時間を代入)
	int  _attackReloadTime; // 近接攻撃用リロード時間(リロード中は近接攻撃不可)
	int  _receptionTime;    // 次の近接攻撃遷移受付時間
	int  _canHitFlag;       // 近接攻撃当たり判定可否(true:可能, false:不可)
	int  _nowDmgHP;         // 発動中近接攻撃のHPへ与えるダメージ量(シールド有)
	int  _nowDmgSld;        // 発動中近接攻撃のシールドへ与えるダメージ量
	int  _nowDmgNorm;       // 発動中近接攻撃のHPへ与えるダメージ量(シールド無)
	bool _isAttack;         // 攻撃発生フラグ(攻撃発動中)

	std::unordered_map<std::string, int> _attackTotalTime;  // 各攻撃モーションの総再生時間を格納する

	static constexpr int ATTACK_NUM = 8;  // 近接攻撃の種類の数
	std::string _attackString[ATTACK_NUM] =  // 各近接攻撃の名前を格納
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l", 
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	const TCHAR* _attackTchar[ATTACK_NUM] =  // 各近接攻撃の名前を格納
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l",
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	// ゲームオーバー用
	int  _gameOverCnt;   // プレイヤー死亡からゲームオーバーまでの時間
	bool _isGameOver;   // ゲームオーバーフラグ

	// その他
	int   _lfAnalogDeg;   // 左アナログスティックの倒した方向(角度)
	float _bsAngle;     // ボスの位置、角度
	bool  _isNearBoss;   // ボスの近くにいるか(true:ボスの近くにいる)	
	bool  _camStateMLS;  // マルチロックオンシステム発動中か


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
		DEAD,            // 死亡
	};
	STATE _state; // プレイヤーの状態

	static constexpr float GRAVITY       = 0.9f; // 重力加速度値
	static constexpr int MAX_BULLET      = 100;  // 最大装弾数
	static constexpr int RELOAD_TIME     = 90;   // 近接・射撃攻撃リロード時間
	static constexpr int AUTO_CHARGE_CNT = 120;  // 自動回復開始カウント
	static constexpr float ANALOG_MIN    = 0.3f; // アナログスティック入力反応の最小値

	PlayerAttack* _attackCall;  // 処理呼び出し：近接攻撃処理
	PlayerMotion* _motionCall;  // 処理呼び出し：モーション切替処理
	PlayerEnergy* _energyCall;  // 処理呼び出し：エネルギー管理処理
	PlayerDash*   _dashCall;    // 処理呼び出し：ダッシュ処理
	PlayerShoot*  _shootCall;   // 処理呼び出し：射撃攻撃処理
	PlayerJump*   _JumpCall;    // 処理呼び出し：ジャンプ処理

	// デバッグ用
	float _len;          // デバッグ用（プレイヤーとボスの距離）
	bool _swCharge;      // デバッグ用(エネルギー消費ON/OFF切替)
};

#include "PlayerAttack.h"
#include "PlayerMotion.h"
#include "PlayerEnergy.h"
#include "PlayerDash.h"
#include "PlayerShoot.h"
#include "PlayerJump.h"