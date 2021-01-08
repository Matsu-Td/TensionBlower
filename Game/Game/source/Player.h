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

	static Player* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetDir() const { return _vDir; }

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
	bool _hit;     // デバッグのみ


	float _inVel;      // 初速度
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
};

/*
// ジャンプ1
float acc = 0.05f;
_inVel -= acc;
_vPos.y += _inVel;
*/