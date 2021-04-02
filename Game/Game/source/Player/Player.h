/**
 * @file   Player.h
 * @brief  プレイヤークラス
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"
#include "../Boss/BossDamage.h"

// プレイヤークラスに関係するクラスの宣言
class PlayerAttack;
class PlayerMotion;
class PlayerEnergy;
class PlayerDash;
class PlayerJump;

/**
 * プレイヤークラス
 */
class Player : public ObjectBase{
	// 下記ファイルからのprivateへのアクセスを可能にする
	friend PlayerAttack;
	friend PlayerMotion;
	friend PlayerEnergy;
	friend PlayerDash;
	friend PlayerJump;
public:
	Player();
	~Player();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	/**
	 * 初期化
	 */
	void Initialize() override;

	/**
	 * フレーム処理：計算
	 */
	void Process() override;

	/**
	 * フレーム処理：描画
	 */
	void Render() override;

	/**
	 * 移動処理
	 */
	void Move();

	/**
	 * 重力処理
	 */
	void Gravity();

	/**
	 * エネルギー溜め処理
	 */
	void Charge();

	/**
	 * マルチロックオンシステム用照準追加
	 */
	void ReticleGeneration();

	/**
	 * ボスとの距離を確認(自動回復用)
	 */
	void CheckDistanceToBoss();

	/**
	 * 当たり判定：ステージ
	 */
	void CollisionToStage();

	/**
	 * 当たり判定：ボスの弾
	 */
	void CollisionToBossBullet();

	/**
	 * 当たり判定：ボス
	 */
	void CollisionToBoss();

	/**
	 * 当たり判定：ボスのレーザー攻撃
	 */
	void CollisionToLaser();

	/**
	 * ゲームオーバー処理
	 */
	void GameOver();

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
	 * ボムの爆発ダメージ
	 */
	void ExplosionDamage();

	/**
	 * プレイヤーインスタンスアクセス用
	 * @return _pInstance プレイヤークラスポインタ
	 */
	static Player* GetInstance() { return _pInstance; }
	static Player* _pInstance;

	static constexpr float GROUND_Y = 0.0f;  // 地上のY座標

	int  _canHitFlag;       // 近接攻撃当たり判定可否(true:可能, false:不可)
private:
	float _analogLength;
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
	
	// エネルギー溜め用
	int  _autoChargeCnt; // エネルギー自動回復開始インターバル
	bool _isCharging;    // エネルギー溜め中か(true:溜め中, false:溜め未実施)
	bool _canAutoCharge; // エネルギー自動回復開始フラグ

	// 近接攻撃用
	int  _attackCnt;        // 攻撃遷移、終了カウント(攻撃モーション総再生時間を代入)
	int  _attackReloadTime; // 近接攻撃用リロード時間(リロード中は近接攻撃不可)
	int  _receptionTime;    // 次の近接攻撃遷移受付時間
	int  _nowDmgHP;         // 発動中近接攻撃のHPへ与えるダメージ量(シールド有)
	int  _nowDmgSld;        // 発動中近接攻撃のシールドへ与えるダメージ量
	int  _nowDmgNorm;       // 発動中近接攻撃のHPへ与えるダメージ量(シールド無)
	int  _hitStart;
	int  _hitEnd;
	bool _isAttack;         // 攻撃発生フラグ(攻撃発動中)

	std::unordered_map<std::string, int> _attackTotalTime;  // 各攻撃モーションの総再生時間を格納する

	static const int ATTACK_NUM = 8;         // 近接攻撃の種類の数
	std::string _attackString[ATTACK_NUM] =      // 各近接攻撃の名前を格納
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l", 
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	const TCHAR* _attackTchar[ATTACK_NUM] =      // 各近接攻撃の名前を格納
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l",
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	// ゲームオーバー用
	int  _gameOverCnt;   // プレイヤー死亡からゲームオーバーまでの時間
	bool _isGameOver;    // ゲームオーバーフラグ

	// その他
	int   _lfAnalogDeg;  // 左アナログスティックの倒した方向(角度)
	float _bsAngle;      // ボスの位置、角度
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
		DEAD,            // 死亡
	};
	STATE _state; // プレイヤーの状態

	static constexpr float GRAVITY       = 0.9f; // 重力加速度値
	static constexpr int AUTO_CHARGE_CNT = 120;  // 自動回復開始カウント
	const int RELOAD_TIME     = 90;   // 近接・射撃攻撃リロード時間
	const float ANALOG_MIN    = 0.3f; // アナログスティック入力反応の最小値

	PlayerAttack* _attackCall;  // 処理呼び出し：近接攻撃処理
	PlayerMotion* _motionCall;  // 処理呼び出し：モーション切替処理
	PlayerEnergy* _energyCall;  // 処理呼び出し：エネルギー管理処理
	PlayerDash*   _dashCall;    // 処理呼び出し：ダッシュ処理
	PlayerJump*   _JumpCall;    // 処理呼び出し：ジャンプ処理

	std::unique_ptr<BossDamage> _bossDamageCall;  	// ボスへのダメージ処理呼び出し
};

#include "PlayerAttack.h"
#include "PlayerMotion.h"
#include "PlayerEnergy.h"
#include "PlayerDash.h"
#include "PlayerJump.h"