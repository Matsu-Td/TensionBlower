#pragma once
#include "appframe.h"


class Player
{
public:
	Player();
	~Player();

	void Initialize();
	void Process();
	void Render();

	static Player* GetInstance() { return _pInstance; }
	VECTOR GetPos() { return _vPos; }

	static Player* _pInstance;

	int _mh;
private:
	const float GROUND_Y = 0.f;  // 床のY座標

	
	int _mhMap;
	VECTOR _vPos;   // 位置
	VECTOR _oldPos;
	VECTOR _vDir;   // 向き
	VECTOR _capsulePos1, _capsulePos2; // 当たり判定用カプセル
	//MV1_COLL_RESULT_POLY_DIM _hitPolyDim;

	int _attachIndex;
	float _totalTime;
	float _playTime;
	float _vel;
	bool _isCanJump;
	bool _hit;     // デバッグのみ

	enum class STATE {
		NONE,
		WAIT,
		WALK,
		DASH,
		JUMP,
	};
	STATE _state; // プレイヤーの状態
};