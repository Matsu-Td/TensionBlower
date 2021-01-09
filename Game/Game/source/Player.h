#pragma once
#include "appframe.h"
#include "PlayerBullet.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize();
	void Process();
	void Render();

	void ShortDash();
	void NormDash();
	void JumpAction();
	void Charging();
	void MortionSwitch();

	static Player* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetDir() const { return _vDir; }
	int GetStatusAttack() const { return _status.nowAtck; }

	static Player* _pInstance;

	int _mh;

	static constexpr float GROUND_Y = 0.f;  // 地上のY座標

private:
	int _mhMap;
	VECTOR _vPos;   // 位置
	VECTOR _oldPos;
	VECTOR _vDir;   // 向き
	VECTOR _capsulePos1, _capsulePos2; // 当たり判定用カプセル

	int _attachIndex;
	float _totalTime;
	float _playTime;
	float _mvSpd;
	bool _isCharging;
	float _bsAngle;
	float _lfAnalogDeg;

	float  _jumpTime;  // ジャンプ時間制御
	bool _isCanJump;   // ジャンプ可否(true:可, false:不可)

	bool _isShortDash;      // 短押しダッシュ中か(true:ダッシュ中)
	int _dashCnt;      // 短押しダッシュカウント

	// プレイヤー状態(モーション)管理
	enum class STATE {  
		NONE,
		WAIT,            // 待機
		WALK,            // 通常移動
		DASH,            // ダッシュ移動
		JUMP,            // ジャンプ
		L_SIDE_DASH,     // 左向きダッシュ移動
		R_SIDE_DASH,     // 右向きダッシュ移動
		BACK_DASH,       // 後向きダッシュ移動
	};
	STATE _state; // プレイヤーの状態

	PlayerBullet _bullet;

	static constexpr float NOR_MV_SPD = 0.8f;
	static constexpr float DASH_MV_SPD = 1.2f;
	static constexpr float CHARGE_MV_SPD = 0.4f;

	static constexpr int MAX_HP = 1000;
	static constexpr int MAX_ENERGY = 6000;

	struct STATUS {
		int hitpoint;
		int energy;
		int nowAtck;
		int wkAtck[4];
		int stAtck[4];
		int shooting;
	};
	STATUS _status;
};

/*
// ジャンプ1
float acc = 0.05f;
_inVel -= acc;
_vPos.y += _inVel;
*/