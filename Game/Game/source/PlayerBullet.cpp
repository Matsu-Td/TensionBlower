
#include "appframe.h"
#include "PlayerBullet.h"
#include "ApplicationMain.h"
#include "ModeGame.h"


PlayerBullet::PlayerBullet(){
//	_mh = ResourceServer::MV1LoadModel("res/model/仮データ/karinotama1.mv1");
	// エフェクトリソースを読み込む。
	// 読み込む時に大きさを指定する。

	_effectResourceHandle = LoadEffekseerEffect("res/effect/effect_shoot.efkefc", 0.05f);
//	_effectResourceHandle = LoadEffekseerEffect("res/effect/laser.efk", 0.05f);
//	DrawEffekseer3D_Begin();
	_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);


	Initialize();
}

PlayerBullet::~PlayerBullet(){

}

void PlayerBullet::Initialize(){
	_shotFlag = false;
}

void PlayerBullet::Process(){
	ObjectBase::Process();

	float mvSpd = 4.0f;   // 弾の速度


	DeleteEffekseerEffect(_effectResourceHandle);
	DeleteEffekseerEffect(_playingEffectHandle);


	float vx, vz;
	vx = cos(_shotAngle) * mvSpd;
	vz = sin(_shotAngle) * mvSpd;

	_vPos.x += vx;
	_vPos.z += vz;

	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	/**
	* 弾の向き調整
	*/
	float deg = _shotAngle * 180.0f / DX_PI_F;
	float angle = (-deg  + ADJ_DEG) / 180.0f * DX_PI_F;

	/**
	* 位置と向き計算
	*/
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _vPos.x, _vPos.y, _vPos.z);
	SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0.0f, angle, 0.0f);

	/**
    * ステージとの当たり判定
    */
	float r = 3.0f; // 当たり判定用半径
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
			if (IsHitStage(*(*itr), r) == true) {				
				modeGame->_objServer.Del(this);
			}
		}
	}
}

void PlayerBullet::Render(){
	
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	//	DrawEffekseer3D_Draw(_playingEffectHandle);
	// Effekseerにより再生中のエフェクトを描画する。
		
		
//	MV1SetPosition(_mh, _vPos);
//	MV1DrawModel(_mh);
};