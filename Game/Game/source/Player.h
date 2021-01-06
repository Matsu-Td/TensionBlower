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
	//MV1_COLL_RESULT_POLY_DIM _hitPolyDim;

	int _attachIndex;
	float _totalTime;
	float _playTime;
	float _mvSpd;
	bool _isCharging;
	bool _hit;     // デバッグのみ

	// ジャンプ関係
	float _inVel;      // 初速度
	float  _jumpTime;  // ジャンプ時間制御
	bool _isCanJump;   // ジャンプ可否(true:可, false:不可)

	enum class STATE {
		NONE,
		WAIT,
		WALK,
		DASH,
		JUMP,
		CHARGE,
	};
	STATE _state; // プレイヤーの状態

	PlayerBullet _bullet;
};