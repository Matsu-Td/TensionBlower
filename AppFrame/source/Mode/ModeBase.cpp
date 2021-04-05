/**
 * @file  ModeBase.cpp
 * @brief モード基底クラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "ModeBase.h"

ModeBase::ModeBase() {
	_szName = "";
	_uid = 1;
	_layer = 0;

	_cntMode = 0;
	_timeMode = 0;
	_timeStep = 0;
	_timeModeBase = 0;
	_timePauseBase = 0;
	_timePauseStep = 0;
	_timeOldFrame = 0;

	SetCallPerFrame(1);
	SetCallOfCount(1);
}

ModeBase::~ModeBase() {
}

/*
 * 初期化
 */
bool ModeBase::Initialize() {

	return true;
}

/*
 * 解放
 */
bool ModeBase::Terminate() {

	return true;
}

/*
 * フレーム処理：計算
 */
bool ModeBase::Process()
{
	return	true;
}

/*
 * フレーム処理：描画
 */
bool ModeBase::Render()
{
	return	true;
}

/*
 * 時間経過処理
 */
void ModeBase::StepTime(unsigned long timeNow) {

	if (_cntMode == 0) {
		_timeMode = 0;
		_timeStep = 0;
		_timeModeBase = timeNow;
		_timePauseBase = 0;
		_timePauseStep = 0;
	}
	else {
		_timeMode = timeNow - _timeModeBase + _timePauseStep;
		_timeStep = timeNow - _timeOldFrame;
	}
	_timeOldFrame = timeNow;
}

/*
 * カウントを進める
 */
void ModeBase::StepCount() {
	_cntMode++;
}
