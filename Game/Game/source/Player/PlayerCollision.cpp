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
#include "PlayerVoice.h"
#include "../Effect/HitEffect.h"
#include "../Sound/Sound.h"

/*
 * 各種当たり判定処理実行 
 */
void Player::AllCollision() {

	CollisionToStage();
	CollisionToBossBullet();
	CollisionToBoss();
	CollisionToLaser();
}

 /*
  * 当たり判定：ステージ
  */
void Player::CollisionToStage() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// ステージとの当たり判定(壁ずり)
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
			if (IsHitStage(*(*itr), 2.0f) == true) {
				VECTOR slideVec;
				slideVec = VCross(_vDir, (*itr)->_hitPolyDim.Dim->Normal);
				slideVec = VCross((*itr)->_hitPolyDim.Dim->Normal, slideVec);
				_vPos = VAdd(_oldPos, slideVec);
				MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);

				while (1) {
					// カプセル位置更新
					_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
					_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

					if (IsHitStage(*(*itr), 2.0f) == false) { break; }

					_vPos = VAdd(_vPos, VScale((*itr)->_hitPolyDim.Dim->Normal, 0.001f));
					MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);
				}
			}
		}
	}
}

/*
 * 当たり判定：ボスとの弾
 */
void Player::CollisionToBossBullet() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
			// 着弾
			if (IsHitLineSegment(*(*itr), (*itr)->_r)) {
				modeGame->_objServer.Del(*itr);
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
			if (IsHitLineSegment(*(*itr), 2.5f)) {
				if (_energy < modeGame->_charaData->_maxEnergy) {
					_energy += modeGame->_charaData->_egAvoid;
				}
				gGlobal._totalGetEnergy += modeGame->_charaData->_egAvoid;
			}
			if (Boss::GetInstance()->_mlsDownFlag) {
				modeGame->_objServer.Del(*itr);
			}
		}
	}
}

/*
 * 当たり判定：ボス
 */
void Player::CollisionToBoss() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitArc_Sphere(*(*itr)) == true) {
				if (_canHitFlag && !_hitFlag) {
					_hitFlag = true;
					_bossDamageCall->AttackDamage(Boss::GetInstance());
					VECTOR tmpPos = MV1GetFramePosition(_mh, MV1SearchFrame(_mh, "weapon3"));
					// ヒットエフェクト生成
					HitEffect* hitEffect = NEW HitEffect(tmpPos);
					modeGame->_objServer.Add(hitEffect);
				}
			}
			if (IsHitLineSegment(*(*itr), (*itr)->_r)) {
				_vPos = VAdd(_vPos, VScale(_oldPos, 0.18f));
			}
		}
	}
}

/*
 * 当たり判定：ボスのレーザー攻撃
 */
void Player::CollisionToLaser() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::LASER) {
			if (IsHitLineSegment(*(*itr), (*itr)->_r) == true) {
				_hitpoint -= 5;
			}
		}
	}
}