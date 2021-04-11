/** 
 * @file   PlayerCollision.cpp
 * @brief  プレイヤーの当たり判定
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Player.h"
#include "../Mode/ModeGame.h"
#include "../Application/ApplicationGlobal.h"
#include "LoadPlayerVoice.h"
#include "../Effect/HitEffect.h"
#include "../Sound/Sound.h"

/*
 * 各種当たり判定処理実行 
 */
void Player::AllCollision() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	for (auto itr : *modeGame->_objServer.List()) {
		CollisionToStage(itr);
		CollisionToBossBullet(itr);
		CollisionToBoss(itr);
		CollisionToLaser(itr);
	}
}

/*
 * 当たり判定：ステージ
 */
void Player::CollisionToStage(ObjectBase* obj) {

	// ステージとの当たり判定(壁ずり)
	if (obj->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
		if (IsHitStage(*obj, 2.0f) == true) {
			VECTOR slideVec;
			slideVec = VCross(_vDir, obj->_hitPolyDim.Dim->Normal);
			slideVec = VCross(obj->_hitPolyDim.Dim->Normal, slideVec);
			_vPos = VAdd(_oldPos, slideVec);
			MV1CollResultPolyDimTerminate(obj->_hitPolyDim);

			while (1) {
				// カプセル位置更新
				_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
				_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

				if (IsHitStage(*obj, 2.0f) == false) { break; }

				_vPos = VAdd(_vPos, VScale(obj->_hitPolyDim.Dim->Normal, 0.001f));
				MV1CollResultPolyDimTerminate(obj->_hitPolyDim);
			}
		}
	}
}

/*
 * 当たり判定：ボスの弾
 */
void Player::CollisionToBossBullet(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

		// 着弾
		if (IsHitLineSegment(*obj, obj->_r)) {
			modeGame->_objServer.Del(obj);
			if (_hitpoint > 0) {
				// 声データ再生(2種類をランダムで再生)
				int voiceNo = rand() % 2;
				if (voiceNo == 0) {
					PlaySoundMem(gPlayerVoice._vc["hidan"], DX_PLAYTYPE_BACK);
				}
				else {
					PlaySoundMem(gPlayerVoice._vc["hukki"], DX_PLAYTYPE_BACK);
				}
				PlaySoundMem(gSound._se["hit_player"], DX_PLAYTYPE_BACK);
				_hitpoint -= modeGame->_charaData->_boss.shotDmg;
				// ヒットエフェクト生成
				VECTOR tmpPos = _vPos;
				tmpPos.y = 4.0f;
				HitEffect* hitEffect = NEW HitEffect(tmpPos);
				modeGame->_objServer.Add(hitEffect);
			}
		}
		// カスリ判定(エネルギー回復)
		if (IsHitLineSegment(*obj, 2.5f)) {
			if (_energy < modeGame->_charaData->_maxEnergy) {
				_energy += modeGame->_charaData->_egAvoid;
			}
			gGlobal._totalGetEnergy += modeGame->_charaData->_egAvoid;
		}
		if (Boss::GetInstance()->_mlsDownFlag) {
			modeGame->_objServer.Del(obj);
		}
	}
}

/*
 * 当たり判定：ボス
 */
void Player::CollisionToBoss(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
		if (IsHitArc_Sphere(*obj) == true) {
			if (_canHitFlag && !_hitFlag) {
				_hitFlag = true;
				Boss::GetInstance()->AttackDamage();
				VECTOR tmpPos = MV1GetFramePosition(_mh, MV1SearchFrame(_mh, "weapon3"));
				// ヒットエフェクト生成
				HitEffect* hitEffect = NEW HitEffect(tmpPos);

				ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
				modeGame->_objServer.Add(hitEffect);
			}
		}
		if (IsHitLineSegment(*obj, obj->_r)) {
			_vPos = VAdd(_vPos, VScale(_oldPos, 0.18f));
		}
	}
}

/*
 * 当たり判定：ボスのレーザー攻撃
 */
void Player::CollisionToLaser(ObjectBase* obj) {

	if (obj->GetType() == ObjectBase::OBJECTTYPE::LASER) {
		if (IsHitLineSegment(*obj, obj->_r) == true) {
			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			_hitpoint -= modeGame->_charaData->_boss.laserDmg;
		}
	}
}