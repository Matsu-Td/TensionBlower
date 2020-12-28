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

private:
	const float GROUND_Y = 0.f;

	int _mh;
	int _mhMap;
	VECTOR _vPos;   // ˆÊ’u
	VECTOR _oldPos;
	VECTOR _vDir;   // Œü‚«
	VECTOR _capsulePos1, _capsulePos2;
	//MV1_COLL_RESULT_POLY_DIM _hitPolyDim;

	int _attachIndex;
	float _totalTime;
	float _playTime;
	float _vel;
	bool _isCanJump;
	bool _hit;

	enum class STATE {
		NONE,
		WAIT,
		WALK,
		DASH,
		JUMP,
	};
	STATE _state;
};