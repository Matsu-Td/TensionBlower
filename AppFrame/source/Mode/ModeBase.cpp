/**
 * @file  ModeBase.cpp
 * @brief ���[�h���N���X
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
 * ������
 */
bool ModeBase::Initialize() {

	return true;
}

/*
 * ���
 */
bool ModeBase::Terminate() {

	return true;
}

/*
 * �t���[�������F�v�Z
 */
bool ModeBase::Process()
{
	return	true;
}

/*
 * �t���[�������F�`��
 */
bool ModeBase::Render()
{
	return	true;
}

/*
 * ���Ԍo�ߏ���
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
 * �J�E���g��i�߂�
 */
void ModeBase::StepCount() {
	_cntMode++;
}
