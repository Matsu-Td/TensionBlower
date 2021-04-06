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

/**
 * @brief プレイヤークラス
 */
class Player : public ObjectBase{
public:
	Player();
	virtual ~Player();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	/**
	 * @brief 初期化
	 */
	void Initialize() override;

	/**
	 * @brief フレーム処理：計算
	 */
	void Process() override;

	/**
	 * @brief フレーム処理：描画
	 */
	void Render() override;

	/**
     * @brief  HP値取得
     * @return プレイヤーの現在のHP値を取得
     */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * @brief  エネルギー量取得
	 * @return プレイヤーの現在のエネルギー量を取得
	 */
	int GetEnergy() const { return _energy; }

	/**
	 * @brief  近接攻撃：シールド状態のボスのHPに与えるダメージ量取得
	 * @return プレイヤーの現在の近接攻撃ダメージ量
	 */
	int GetNowDmgHP() const { return _nowDmgHP; }

	/**
	 * @brief  近接攻撃：シールド状態のボスのシールドに与えるダメージ量取得
	 * @return プレイヤーの現在の近接攻撃ダメージ量
	 */
	int GetNowDmgSld() const { return _nowDmgSld; }

	/**
	 * @brief  近接攻撃：通常状態のボスのHPに与えるダメージ量取得
	 * @return プレイヤーの現在の近接攻撃ダメージ量
	 */
	int GetNowDmgNorm() const { return _nowDmgNorm; }

	/**
	 * @brief ボムの爆発ダメージ
	 */
	void ExplosionDamage();

	/**
     * @brief  プレイヤーインスタンスアクセス用
     * @return Playerのインスタンス
     */
	static Player* GetInstance() { return _pInstance; }
	static Player* _pInstance;

	int _canHitFlag;  // 近接攻撃当たり判定可否(true:可能, false:不可)

private:
	/**
	 * @brief 移動処理
	 */
	void Move();

	/**
	 * @brief 重力処理
	 */
	void Gravity();

	/**
	 * @brief エネルギー溜め処理
	 */
	void Charge();

	/**
	 * @brief マルチロックオンシステム用照準追加
	 */
	void ReticleGeneration();

	/**
	 * @brief ボスとの距離を確認(自動回復用)
	 */
	void CheckDistanceToBoss();

	/**
     * @brief 各種当たり判定処理実行
     */
	void AllCollision();

	/**
	 * @brief 当たり判定：ステージ
	 */
	void CollisionToStage();

	/**
	 * @brief 当たり判定：ボスの弾
	 */
	void CollisionToBossBullet();

	/**
	 * @brief 当たり判定：ボス
	 */
	void CollisionToBoss();

	/**
	 * @brief 当たり判定：ボスのレーザー攻撃
	 */
	void CollisionToLaser();

	/**
	 * @brief 死亡処理＆ゲームオーバーへ移行
	 */
	void Death();

	/**
	 * モーションの名前で指定したモデルのモーションをアタッチする
	 * @param  animName モーション名
	 * @return モーション番号
	 */
	int AttachAnim(const TCHAR* animName) const;

	/**
	 * @brief モーション切替処理
	 */
	void MotionSwitching();

	/**
	 * @brief ジャンプ処理
	 */
	void Jump();

	/**
	 * @brief エネルギー消費処理
	 * @param costEnergy 消費するエネルギー量
	 */
	void CostEnergy(int costEnergy);

	/**
	 * @brief エネルギーの回復、消費処理
	 */
	void EnergyManager();

	/**
	 * @brief 移動、ダッシュモーション切替処理
	 * @brief 左アナログスティックの倒した角度によってキャラの状態、モーションを遷移
	 */
	void LeftAnalogDeg();

	/**
	 * @brief ダッシュ処理
	 */
	void Dash();

	/**
	 * @brief 近接攻撃のダメージ量を近接攻撃の種類によって切替
	 * @param player  プレイヤークラスオブジェクトのポインタ
	 */
	void SwitchAttackDamage();

	/**
	 * @brief 現在発生中の近接攻撃ダメージ量を設定する
	 * @param dmgHP   シールド状態のボスのヒットポイントに与えるダメージ量
	 * @param dmgSld  シールド状態のボスのシールドに与えるダメージ量
	 * @param dmgNorm シールドがない状態のボスのヒットポイントに与えるダメージ量
	 */
	void SetAttackDamage(int dmgHP, int dmgSld, int dmgNorm);

	/**
	 * @brief 各近接攻撃へのキー入力処理
	 */
	void AttackAction();

	/**
	 * @brief 近接攻撃処理(初手のみ)
	 */
	void FirstAttack();

	/**
	 * @brief 近接攻撃処理(2発目以降)
	 */
	void SecondAttack();

	/**
	 * @brief 攻撃発生時の声データを再生する
	 * @param voiceName 再生する声データの名前
	 */
	void PlayAttackVoice(std::string voiceName);

	/**
	 * @brief 弱近接攻撃のヒット判定時間を設定する
	 */
	void SetWeakHitTime();

	/**
	 * @brief 強近接攻撃のヒット判定時間を設定する
	 */
	void SetStrongHitTime();

private:
	float _analogLength; // 左アナログスティックの入力、倒した大きさ

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
	int  _hitStartCnt;      // 近接攻撃の当たり判定発生開始カウント
	int  _hitEndCnt;        // 近接攻撃の当たり判定発生終了カウント
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

	/**
	 * @brief プレイヤー状態遷移用
	 */
	enum class STATE {
		NONE,          // 無し
		WAIT,          // 待機
		WALK,          // 通常移動
		FOR_DASH,      // 前方ダッシュ移動
		JUMP,          // ジャンプ
		LEFT_MOVE,     // 左方移動
		RIGHT_MOVE,    // 右方移動
		BACK_MOVE,     // 後方移動
		LEFT_DASH,     // 左方ダッシュ移動
		RIGHT_DASH,    // 右方ダッシュ移動
		BACK_DASH,     // 後方ダッシュ移動
		WEAK_ATCK1,    // 弱近接攻撃1
		WEAK_ATCK2,    // 弱近接攻撃2
		WEAK_ATCK3,    // 弱近接攻撃3
		WEAK_ATCK4,    // 弱近接攻撃4
		STRG_ATCK1,    // 強近接攻撃1
		STRG_ATCK2,    // 強近接攻撃2
		STRG_ATCK3,    // 強近接攻撃3
		STRG_ATCK4,    // 強近接攻撃4
		DEATH,         // 死亡
	};
	STATE _state;    // プレイヤーの状態
	STATE _oldState; // 処理前のプレイヤーの状態
	
	// 定数
	const float GROUND_Y      = 0.0f;  // 地上のY座標
	const float GRAVITY       = 0.9f;  // 重力加速度値
	const float ANALOG_MIN    = 0.3f;  // アナログスティック入力反応の最小値
	const float IN_VEL        = 5.0f;         // 初速
	const float MULT_HALF     = 0.5f;      // 1/2乗算
	const float JUMP_CNT      = 0.2f;       // ジャンプ時間

	const int SHORT_DASH_CNT     = 10;     // 短押しダッシュ移動時間
	const int AUTO_CHARGE_CNT    = 120;   // エネルギー自動回復開始カウント
	const int RELOAD_TIME        = 90;    // 近接・射撃攻撃リロード時間
	const int ANALOG_REG_FOR     = 120;    // 左アナログスティックを倒す前方向判定の角度範囲(ターゲットロック中のみ使用)
	const int ANALOG_REG_OTHER   = 45;   // 左アナログスティックを倒す前方向以外の角度範囲(ターゲットロック中のみ使用)
	const int RECEPTION_TIME     = 30;     // 次近接攻撃受付時間
	const int ATTACK_RELOAD_TIME = 90; // 近接・射撃攻撃リロード時間

	std::unique_ptr<BossDamage> _bossDamageCall;  	// ボスへのダメージ処理呼び出し

	/**
	 * @brief 強近接攻撃への派生関連処理
	 * @param attackEnergy 指定された強近接攻撃での消費エネルギー量
	 * @param nextState    派生する強近接攻撃の種類
	 * @param attackName   派生する強近接攻撃の名前(攻撃モーション時間セット用)
	 */
	void NextStrongAttack(int attackEnergy, STATE nextState, std::string attackName);

	/**
	 * @brief 弱近接攻撃への派生関連処理
	 * @param nextState    派生する弱近接攻撃の種類
	 * @param attackName   派生する弱近接攻撃の名前(攻撃モーション時間セット用)
	 */
	void NextWeakAttack(STATE nextState, std::string attackName);
};