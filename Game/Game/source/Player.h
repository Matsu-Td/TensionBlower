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
	int _mh;
	VECTOR _vPos;   // ˆÊ’u
	VECTOR _vDir;   // Œü‚«

	int _attachIndex;
	float _totalTime;
	float _playTime;

	enum class STATE {
		NONE,
		WAIT,
		WALK,
		JUMP,
	};
	STATE _state;
};