/**
 * @file   Explosion.cpp
 * @brief  �{���U���̔����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#include "Explosion.h"
#include "../Mode/ModeGame.h"
#include "../Boss/Boss.h"
#include "../Player/Player.h"
#include "../Sound/Sound.h"
#include "../Camera/Camera.h"


Explosion::Explosion(VECTOR pos, bool repelFlag) {
	// �������A�������Đ�
	PlaySoundMem(gSound._se["explosion1"], DX_PLAYTYPE_BACK);

	_effectHandle = ResourceServer::LoadEffekseerEffect("res/effect/explosion/explosion.efkefc", 1.0f);
	_playingHandle = PlayEffekseer3DEffect(_effectHandle);

	_vPos = pos;
	_repelFlag = repelFlag;

	Initialize();
}

Explosion::~Explosion() {
	StopEffekseer3DEffect(_playingHandle);
}

/**
 * ������
 */
void Explosion::Initialize() {

	_effectCnt = 0;
	_r = 0.0f;
}

/**
 * �{�X�Ƃ̓����蔻��
 */
void Explosion::CollisionToBoss() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitLineSegment(*(*itr), _r)) {
				// �q�b�g�|�C���g�ւ̃_���[�W�F6�t���[�����Ƀ_���[�W����
				if (_effectCnt % 6 == 0) {
					_bossDamageCall->ExplosionDamageHP(Boss::GetInstance());
				}
				// �V�[���h�ւ̃_���[�W�F���t���[���_���[�W����
				_bossDamageCall->ExplosionDamageShield(Boss::GetInstance());
			}
		}
	}
}

/**
 * �v���C���[�Ƃ̓����蔻��
 */
void Explosion::CollisionToPlayer() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			if (IsHitLineSegment(*(*itr), _r)) {
				Player::GetInstance()->ExplosionDamage();

			}
		}
	}
}

/**
 * �t���[�������F�v�Z
 */
void Explosion::Process(){

	_effectCnt++;

	// �����蔻��p���a���G�t�F�N�g�T�C�Y�ɍ��킹�ď��X�ɑ傫������
	_r += 0.3f;
	if (_r >= MAX_RADIUS) {
		_r = MAX_RADIUS;
	}

	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	SetPosPlayingEffekseer3DEffect(_playingHandle, _vPos.x, _vPos.y, _vPos.z);

	// ���Đ����Ԃ��}������G�t�F�N�g�폜
	if (_effectCnt >= ALL_EFFECT_TIME) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_objServer.Del(this);
	}

	// �v���C���[�ɒe���Ԃ��ꂽ�e���ǂ���
	if (_repelFlag) {
		// �{�X�ɂ̂ݓ����蔻��
		CollisionToBoss();
	}
	else {
		// �v���C���[�̂ݓ����蔻��
		CollisionToPlayer();
	}
}

/**
 * �t���[�������F�`��
 */
void Explosion::Render(){

}
