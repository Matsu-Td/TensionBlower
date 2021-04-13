/**
 * @file   PlayerMotion.cpp
 * @brief  �v���C���[���[�V�����ؑ֏���
 *
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Camera/Camera.h"

/*
 * ���[�V�������Ŏw�肵�����f���̃��[�V�������A�^�b�`����
 */
void Player::AttachAnim(const TCHAR* animName) {

	_attachIndex       = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, animName), -1, FALSE);
	_attachIndexShadow = MV1AttachAnim(_shadowModel, MV1GetAnimIndex(_shadowModel, animName), -1, FALSE);
}

/*
 * ���[�V�����ؑ�
 */
void Player::MotionSwitching() {

	Camera::STATE camState = Camera::GetInstance()->GetState();

	// �}���`���b�N�I���V�X�e�����������烂�[�V�������uWAIT�v�ɂ���
	if (camState == Camera::STATE::MLS_LOCK) {
		_state = STATE::WAIT;
	}

	if (_oldState == _state) {
		_playTime += 1.0f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			MV1DetachAnim(_shadowModel, _attachIndex);
			_attachIndex = -1;
		}
		switch (_state) {
		case STATE::WAIT:
			AttachAnim("wait");
			break;
		case STATE::WALK:
			AttachAnim("ahead");
			break;
		case STATE::JUMP:
			AttachAnim("junp_up");
			break;
		case STATE::FOR_DASH:
			AttachAnim("d_ahead");
			break;
		case STATE::LEFT_MOVE:
			AttachAnim("left");
			break;
		case STATE::RIGHT_MOVE:
			AttachAnim("right");
			break;
		case STATE::BACK_MOVE:
			AttachAnim("back");
			break;
		case STATE::LEFT_DASH:
			AttachAnim("d_left");
			break;
		case STATE::RIGHT_DASH:
			AttachAnim("d_right");
			break;
		case STATE::BACK_DASH:
			AttachAnim("d_back");
			break;
		case STATE::WEAK_ATCK1:
		case STATE::WEAK_ATCK2:
		case STATE::WEAK_ATCK3:
		case STATE::WEAK_ATCK4:
			AttachAnim("slash_l");
			break;
		case STATE::STRG_ATCK1:
		case STATE::STRG_ATCK2:
		case STATE::STRG_ATCK3:
		case STATE::STRG_ATCK4:
			AttachAnim("slash_h");
			break;
		case STATE::DEATH:
			AttachAnim("dead");
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}
}