#pragma once
#include "appframe.h"
#include "PlayerBullet.h"
#include "BulletServer.h"
#define  CHARA_DATA (modeGame->_charaData)

class Player : public ObjectBase
{
public:
	Player();
	~Player();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	void Initialize();
	void Process();
	void Render();

	void ShortDash();
	void NormDash();
	void JumpAction();
	void Charging();
	void MortionSwitch();
	void AttackAction();
	void SetAttackDamage();
	MATRIX MV1GetFrameRotateMatrix(int MHandle, int FrameIndex, double Xaxis, double Yaxis, double Zaxis, double modelScale);


	/**
	* カメラロック中の移動、ダッシュモーション切替処理／
	* 左アナログスティックの倒した角度によってキャラの状態、モーションを遷移
	* @param length  := sqrt(lx * lx + ly * ly) 左アナログスティックの入力値
	*/
	void LeftAnalogDeg(float length);

	static Player* GetInstance() { return _pInstance; }

	int GetEnergy() { return _energy; }
	int GetNowDmgHP() const { return _nowDmgHP; }
	int GetNowDmgSld() const { return _nowDmgSld; }
	int GetNowDmgNorm() const { return _nowDmgNorm; }

	static Player* _pInstance;

	static constexpr float GROUND_Y = 0.f;  // 地上のY座標

private:
	// ステータス関連
	int _hitpoint;       // ヒットポイント値
	int _energy;         // エネルギー値
	int _nowDmgHP;        // 現在の近接攻撃の種類(ボスへのダメージ用)
	int _nowDmgSld;
	int _nowDmgNorm;
	int _wkAtck[4];
	int _stAtck[4];
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
	bool _isCharging;    // 溜め中か(true:溜め中, false:溜め未実施)
	bool _swCharge;      // デバッグ用(エネルギー消費ON/OFF切替)
	bool _atChargeFlag;  // エネルギー自動回復開始フラグ
	int _atChargeCnt;    // エネルギー自動回復開始インターバル

	// 近接攻撃関連
	bool _attackFlag;      // 攻撃発生フラグ(攻撃発動中)
	int _attackCnt;        // 攻撃遷移、終了カウント(攻撃モーション総再生時間を代入)
	int _attackReloadTime; // 近接攻撃用リロード時間(リロード中は近接攻撃不可)
	int _receptionTime;    // 次の近接攻撃遷移受付時間
	int _canHitFlag;       // 近接攻撃当たり判定可否(true:可能, false:不可)
	std::unordered_map<std::string, int> _attackTotalTime;  // 各攻撃モーションの総再生時間を格納する

	// その他
	bool _nearPosFlag;   // ボスの近くにいるとき
	float _bsAngle;      // ボスの位置、角度
	int _lfAnalogDeg;    // 左アナログスティックの倒した方向(角度)
	int _gameOverCnt;    // プレイヤー死亡からゲームオーバーまでの時間
	bool _gameOverFlag;
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

	void EnergyManager(STATE oldState);

	static constexpr float GRAVITY = 0.9f;       // 重力
	static constexpr int SHORT_DASH_CNT = 10;    // 短押しダッシュ時間
	static constexpr int MAX_BULLET = 100;       // 最大装弾数
	static constexpr int AT_CHARGE_CNT = 120;    // 自動回復開始カウント
	static constexpr int RECEPTION_TIME = 30;    // 次近接攻撃受付時間
	static constexpr int RELOAD_TIME = 90;  // 近接・射撃攻撃リロード時間

	// デバッグ用
	float _len;          // デバッグ用（プレイヤーとボスの距離）
};

/*
// ジャンプ1
float acc = 0.05f;
_inVel -= acc;
_vPos.y += _inVel;
*/

//	static constexpr float NOR_MV_SPD = 0.8f;    // 通常速度
//	static constexpr float DASH_MV_SPD = 1.2f;   // ダッシュ速度
//	static constexpr float CHARGE_MV_SPD = 0.2f; // 溜め行動中の速度
//	static constexpr int MAX_HP = 1000;          // 最大ヒットポイント量
//	static constexpr int MAX_ENERGY = 6000;      // 最大エネルギー量
//	static constexpr int JUMP_ENERGY = 1200;     // ジャンプのエネルギー消費量
//	static constexpr int DASH_ENERGY = 600;      // 短押しダッシュ時のエネルギー消費量
//	static constexpr int AT_CHARGE = 2;          // 1fあたりエネルギー自動回復量