#pragma once

#include "appframe.h"

class PlayerStatus {
public:
	PlayerStatus();
	~PlayerStatus();

	void Render();

private:
	int _cgName;
	int _cgFrame;
	int _cgFrameBg;
	int _cgBarHP;
	int _cgBarEnergy;
	int _cgRemainFrame;

	static constexpr int ALL_NUM = 10;
	int _cgRemainNum[ALL_NUM];

	const TCHAR* _numString[ALL_NUM]=
	{"res/remain_0.png","res/remain_1.png", "res/remain_2.png", "res/remain_3.png", "res/remain_4.png", 
	 "res/remain_5.png","res/remain_6.png", "res/remain_7.png", "res/remain_8.png", "res/remain_9.png" };


};