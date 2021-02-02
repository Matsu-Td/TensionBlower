
#include "appframe.h"
#include "PlayerBullet.h"
#include "ApplicationMain.h"
#include "ModeGame.h"


PlayerBullet::PlayerBullet(){
//	_mh = ResourceServer::MV1LoadModel("res/model/���f�[�^/karinotama1.mv1");
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	// �ǂݍ��ގ��ɑ傫�����w�肷��B

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

	float mvSpd = 4.0f;   // �e�̑��x


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
	* �e�̌�������
	*/
	float deg = _shotAngle * 180.0f / DX_PI_F;
	float angle = (-deg  + ADJ_DEG) / 180.0f * DX_PI_F;

	/**
	* �ʒu�ƌ����v�Z
	*/
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _vPos.x, _vPos.y, _vPos.z);
	SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0.0f, angle, 0.0f);

	/**
    * �X�e�[�W�Ƃ̓����蔻��
    */
	float r = 3.0f; // �����蔻��p���a
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
	
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	//	DrawEffekseer3D_Draw(_playingEffectHandle);
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
		
		
//	MV1SetPosition(_mh, _vPos);
//	MV1DrawModel(_mh);
};