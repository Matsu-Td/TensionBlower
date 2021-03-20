
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
	_tmMode = 0;
	_tmStep = 0;
	_tmModeBase = 0;
	_tmPauseBase = 0;
	_tmPauseStep = 0;
	_tmOldFrame = 0;

	SetCallPerFrame(1);
	SetCallOfCount(1);
}

ModeBase::~ModeBase() {
}

/**
 * 初期化
 */
bool ModeBase::Initialize() {

	return true;
}

/**
 * 解放
 */
bool ModeBase::Terminate() {

	return true;
}

/**
 * フレーム処理：計算
 */
bool ModeBase::Process()
{
	return	true;
}

/**
 * フレーム処理：描画
 */
bool ModeBase::Render()
{
	return	true;
}

/**
 * 時間経過処理
 */
void ModeBase::StepTime(unsigned long tmNow) {

	if (_cntMode == 0) {
		_tmMode = 0;
		_tmStep = 0;
		_tmModeBase = tmNow;
		_tmPauseBase = 0;
		_tmPauseStep = 0;
	}
	else {
		_tmMode = tmNow - _tmModeBase + _tmPauseStep;
		_tmStep = tmNow - _tmOldFrame;
	}
	_tmOldFrame = tmNow;
}

/**
 * カウントを進める
 */
void ModeBase::StepCount() {
	_cntMode++;
}
