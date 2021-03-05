/**
 * @file   BossBomb.cpp
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#include "BossBomb.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"
#include "Explosion.h"
#include "Sound.h"

BossBomb::BossBomb(VECTOR pos) {

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bomb.mv1");
	_vPos = pos;

	Initialize();
}

BossBomb::~BossBomb() {

}

void BossBomb::Initialize() {

	_shotCnt = 0;
	_shotSpd = 2.0f;
	_upSpd = 0.5f;
	_state = STATE::UP;
}

void BossBomb::Process() {

	// �_���܂ł̃J�E���g
	_shotCnt++;

	// �㏸����
	if (_state == STATE::UP) {
		_vPos.y += _upSpd;
		if (_shotCnt >= UP_CNT) {
			_shotCnt = 0;          // �J�E���g���Z�b�g
			_state = STATE::STOP;  // ��~��ԂɈڍs
		}
	}

	// ��~����
	if (_state == STATE::STOP) {
		if (_shotCnt >= STOP_CNT) {
			_shotCnt = 0;
			// �v���C���[�ʒu���擾
			VECTOR plPos = Player::GetInstance()->GetPos();
			plPos.y = 0.0f;          // �v���C���[�̑���(�X�e�[�W��)���^�[�Q�b�g�Ƃ���
			_vTarg = plPos;          // �v���C���[���^�[�Q�b�g�Ƃ���
			_state = STATE::SNIPER;  // �ˌ���ԂɈڍs
		}
	}

	// �_������
	if (_state == STATE::SNIPER) {
		// �^�[�Q�b�g�Ɍ������ă{���𔭎˂���
		VECTOR targ = VSub(_vTarg, _vPos);
		targ = VNorm(targ);
		targ = VScale(targ, 2.0f);
		_vPos = VAdd(_vPos, targ);
	}

	// �X�e�[�W���܂ŉ��~������{�����폜
	if (_vPos.y <= 0.0f) {
		PlaySoundMem(gSound._se["explosion1"], DX_PLAYTYPE_BACK);
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Explosion* explosion = NEW Explosion(_vPos);
		modeGame->_objServer.Add(explosion);
		modeGame->_objServer.Del(this);

	}
}

void BossBomb::Render() {
	
	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1SetRotationXYZ(_mh, VGet(0.f, (_shotAngle + 270.f) / 180.f * DX_PI_F, 0.f));
	MV1DrawModel(_mh);

	DrawFormatString(960, 540, GetColor(255, 0, 0), "%d",_state);
}
