#pragma once
#include "appframe.h"
#include "PlayerBullet.h"
#include "BulletServer.h"

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


	/**
	* カメラロック中の移動、ダッシュモーション切替処理／
	* 左アナログスティックの倒した角度によってキャラの状態、モーションを遷移
	* @param length  := sqrt(lx * lx + ly * ly) 左アナログスティックの入力値
	*/
	void LeftAnalogDeg(float length);

	static Player* GetInstance() { return _pInstance; }
//	VECTOR GetPos() const { return _vPos; }
//	VECTOR GetDir() const { return _vDir; }
	int GetEnergy() { return _status.energy; }
	int GetStatusAttack() const { return _status.nowAtck; }

	static Player* _pInstance;



	static constexpr float GROUND_Y = 0.f;  // 地上のY座標

private:
	VECTOR _oldPos;     // 移動処理前の位置保存

	bool _isCharging;   // 溜め中か(true:溜め中, false:溜め未実施)
	float _bsAngle;     // ボスの位置、角度
	int _lfAnalogDeg;   // 左アナログスティックの倒した方向(角度)

	bool _isCanJump;     // ジャンプ可否(true:可, false:不可)
	float  _jumpTime;    // ジャンプ時間制御

	bool _isDash;       // ダッシュ開始(全種類)
	bool _isShortDash;   // 短押しダッシュ中か(true:ダッシュ中)
	bool _isCanLongDash; // 長押しダッシュ可否(true:可能, false:不可)
	int _shortDashTime;   // 短押しダッシュ移動時間

	bool _canShotFlag;   // 射撃可否(true:可能, false:不可)
	bool _shotZeroFlag;  // 装弾数ゼロフラグ(true:装弾数「0」状態, false:装弾が「1」以上ある状態)
	int _shotInterval;   // 弾の発射間隔
	int _reloadTime;     // リロード開始までの時間

	bool _atChargeFlag;  // エネルギー自動回復開始フラグ
	int _atChargeCnt;    // エネルギー自動回復開始インターバル

	int _gameOverCnt;

	bool _camStateMLS;

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

	static constexpr float NOR_MV_SPD = 0.8f;    // 通常速度
	static constexpr float DASH_MV_SPD = 1.2f;   // ダッシュ速度
	static constexpr float CHARGE_MV_SPD = 0.2f; // 溜め行動中の速度
	static constexpr int SHORT_DASH_CNT = 10;    // 短押しダッシュ時間

	static constexpr int MAX_HP = 1000;          // 最大ヒットポイント量
	static constexpr int MAX_ENERGY = 6000;      // 最大エネルギー量
	static constexpr int MAX_BULLET = 100;       // 最大装弾数
	static constexpr int JUMP_ENERGY = 1200;      // ジャンプのエネルギー消費量
	static constexpr int DASH_ENERGY = 600;     // 短押しダッシュ時のエネルギー消費量
	static constexpr int AT_CHARGE = 2;          // 1fあたりエネルギー自動回復量
	static constexpr int AT_CHARGE_CNT = 120;    // 自動回復開始カウント

	struct STATUS {
		int hitpoint;
		int energy;
		int nowAtck;
		int wkAtck[4];
		int stAtck[4];
		int shooting;
		int bulletNum;
	};
	STATUS _status;
};

/*
// ジャンプ1
float acc = 0.05f;
_inVel -= acc;
_vPos.y += _inVel;
*/