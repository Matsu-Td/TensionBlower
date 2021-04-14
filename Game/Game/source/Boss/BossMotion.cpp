/** 
 * @file   BossMotion.cpp
 * @brief  �{�X�̃��[�V�����ؑ֏���
 * 
 * @author matsuo tadahiko
 * @date   2021/04/07
 */

#include "Boss.h"

using namespace tensionblower::boss;

/*
 * ���[�V�����ؑ֏���
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
			_attachIndex = -1; // �ʏ�̓��[�V��������
			break;
		case STATE::DOWN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "down"), -1, FALSE);
			break;
		case STATE::RETURN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "return"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}
}