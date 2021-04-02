/**
 * @file   PlayerMotion.cpp
 * @brief  プレイヤーモーション切替
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "PlayerMotion.h"
#include "../Camera/Camera.h"

 /**
  * プレイヤーモーション切替
  */
void PlayerMotion::SwitchMotion(Player* player, Player::STATE oldState) {

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// マルチロックオンシステム発動したらモーションを「WAIT」にする
	if (camState == Camera::STATE::MLS_LOCK) {
		player->_state = Player::STATE::WAIT;
	}

	if (oldState == player->_state) {
		player->_playTime += 1.0f;
	}
	else {
		if (player->_attachIndex != -1) {
			MV1DetachAnim(player->_mh, player->_attachIndex);
			player->_attachIndex = -1;
		}
		switch (player->_state) {
		case Player::STATE::WAIT:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "wait"), -1, FALSE);
			break;
		case Player::STATE::WALK:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "ahead"), -1, FALSE);
			break;
		case Player::STATE::JUMP:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "junp_up"), -1, FALSE);
			break;
		case Player::STATE::FOR_DASH:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "d_ahead"), -1, FALSE);
			break;
		case Player::STATE::LEFT_MOVE:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "left"), -1, FALSE);
			break;
		case Player::STATE::RIGHT_MOVE:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "right"), -1, FALSE);
			break;
		case Player::STATE::BACK_MOVE:
			 player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "back"), -1, FALSE);
			break;
		case Player::STATE::LEFT_DASH:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "d_left"), -1, FALSE);
			break;
		case Player::STATE::RIGHT_DASH:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "d_right"), -1, FALSE);
			break;
		case Player::STATE::BACK_DASH:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "d_back"), -1, FALSE);
			break;
		case Player::STATE::WEAK_ATCK1:
		case Player::STATE::WEAK_ATCK2:
		case Player::STATE::WEAK_ATCK3:
		case Player::STATE::WEAK_ATCK4:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "slash_l"), -1, FALSE);
			break;
		case Player::STATE::STRG_ATCK1:
		case Player::STATE::STRG_ATCK2:
		case Player::STATE::STRG_ATCK3:
		case Player::STATE::STRG_ATCK4:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "slash_h"), -1, FALSE);
			break;
		case Player::STATE::DEAD:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "dead"), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		player->_totalTime = MV1GetAttachAnimTotalTime(player->_mh, player->_attachIndex);

		player->_playTime = 0.0f;
	}
}