
/**
 * @file  PlayerMotion.h
 * @brief プレイヤーモーション切替
 * 
 * @date 2021-02-13
 */

#include "PlayerMotion.h"

 /**
  * プレイヤーモーション切替
  */
void PlayerMotion::SwitchMotion(Player* player, Player::STATE oldState) {

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
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "waitmove"), -1, FALSE);
			break;
		case Player::STATE::WALK:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "run"), -1, FALSE);
			break;
		case Player::STATE::JUMP:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::FOR_DASH:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::LEFT_MOVE:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::RIGHT_MOVE:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::BACK_MOVE:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::LEFT_DASH:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::RIGHT_DASH:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::BACK_DASH:
			//_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case Player::STATE::WEAK_ATCK1:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::WEAK_ATCK2:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::WEAK_ATCK3:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::WEAK_ATCK4:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::STRG_ATCK1:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::STRG_ATCK2:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::STRG_ATCK3:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::STRG_ATCK4:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "player_lattack04"), -1, FALSE);
			break;
		case Player::STATE::SHOT_ATCK:
			player->_attachIndex = MV1AttachAnim(player->_mh, MV1GetAnimIndex(player->_mh, "shoot"), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		player->_totalTime = MV1GetAttachAnimTotalTime(player->_mh, player->_attachIndex);

		player->_playTime = 0.0f;
	}

	if (!player->_attackFlag) {
		if (player->_playTime >= player->_totalTime) {
			player->_playTime = 0.0f;
		}
	}
}