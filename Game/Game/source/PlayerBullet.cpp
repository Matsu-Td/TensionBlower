/**
 * @file   PlayerBullet.cpp
 * @brief  プレイヤー射撃用の弾移動処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */
//
//#include "appframe.h"
//#include "ModeGame.h"
//#include "Player.h"
//#include "PlayerBullet.h"
//
//PlayerBullet::PlayerBullet(VECTOR pos, float angle){
//
//	_effectHandle = ResourceServer::LoadEffekseerEffect("res/effect/effect_shoot.efkefc", 0.04f);
//	_playingHandle = PlayEffekseer3DEffect(_effectHandle);
//
//	_vPos = pos;
//	_shotAngle = angle;
//	Initialize();
//}
//
//PlayerBullet::~PlayerBullet(){
//
//	StopEffekseer3DEffect(_playingHandle);
//}
//
//void PlayerBullet::Initialize(){
//	
//	_shotFlag = false;
//	_mvSpd = 4.0f;
//	_r = 1.5f;
//}
//
//void PlayerBullet::Process(){
//	ObjectBase::Process();
//
//	float vx, vz;
//	vx = cos(_shotAngle) * _mvSpd;
//	vz = sin(_shotAngle) * _mvSpd;
//
//	_vPos.x += vx;
//	_vPos.z += vz;
//	
//	_capsulePos1 = _vPos;
//	_capsulePos2 = _vPos;
//
//	// 弾の向き調整
//	float deg = _shotAngle * 180.0f / DX_PI_F;
//	float angle = (-deg + ADJ_DEG) / 180.0f * DX_PI_F;
//
//	// 位置と向き計算
//	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);
//	SetRotationPlayingEffekseer3DEffect(_playingHandle, 0.0f, angle, 0.0f);
//
//
//	// ステージとの当たり判定
//	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
//	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
//		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
//			if (IsHitStage(*(*itr), _r) == true) {				
//				modeGame->_objServer.Del(this);
//				MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);
//				StopEffekseer3DEffect(_playingHandle); // 再生停止
//			}
//		}
//	}
//}
//
//void PlayerBullet::Render(){
//
//}