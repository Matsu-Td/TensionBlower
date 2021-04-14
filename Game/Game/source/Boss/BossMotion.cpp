/** 
 * @file   BossMotion.cpp
 * @brief  ボスのモーション切替処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"

using namespace tensionblower::boss;

/*
 * モーション切替処理
 */
void Boss::MotionSwitch() {

	if (_oldState == _state) {
		_playTime += 1.0f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
		}
		switch (_state) {
		case STATE::NORMAL:
			_attachIndex = -1; // 通常はモーション無し
			break;
		case STATE::DOWN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "down"), -1, FALSE);
			break;
		case STATE::RETURN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "return"), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}
}