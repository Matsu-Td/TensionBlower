/**
 * @file   BossBullet.cpp
 * @brief  �{�X�̒e������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "BossBullet.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "ModeGame.h"

BossBullet::BossBullet(){

	_mh = ResourceServer::MV1LoadModel("res/model/boss/bullet.mv1");

	_cg[0] = ResourceServer::LoadGraph("res/���f��/���b�N�\.png");
	_cg[1] = ResourceServer::LoadGraph("res/���f��/���b�N�m��.png");
	Initialize();
}

BossBullet::~BossBullet(){

}

void BossBullet::Initialize(){

	_setAngle = 45.0f;
	_shotCnt = 0;
	_mlsCnt = 0;
	_pattern = 0;
	_camStateMLS = false;
	_hitX = _hitY = -25.0f;
	_hitW = _hitH = 25.0f;
	_canLockFlag = false;
	_repelFlag = false;
	_bulletDir = 1.0f;
}

void BossBullet::Shot(){
	
	int camState = Camera::GetInstance()->GetCameraState();  // �J�����̏�Ԃ��擾

	if(camState == Camera::STATE::MLS_LOCK){
		_mvSpd = _shotSpd * 0.01f; // �}���`���b�N�I���V�X�e�����͑��x0.1�{
		_camStateMLS = true;
	}
	else {
		_mvSpd = _shotSpd;   // �ʏ펞�̒e�̑��x
		_camStateMLS = false;
	}
	
	float vx, vz;
	vx = cos(_shotAngle / 180.0f * DX_PI_F) * _mvSpd * _bulletDir;
	vz = sin(_shotAngle / 180.0f * DX_PI_F) * _mvSpd * _bulletDir;
	_vPos.x += vx;
	_vPos.z += vz;
}


void BossBullet::Process(){

	int trg = ApplicationMain::GetInstance()->GetTrg();

	VECTOR plPos = Player::GetInstance()->GetPos();
	float sx = plPos.x - _vPos.x;
	float sz = plPos.z - _vPos.z;
	float length = sqrt(sx * sx + sz * sz);
	Shot(); // �e��������

	_scrnPos = ConvWorldPosToScreenPos(_vPos);  // ���[���h���W �� �X�N���[�����W�֕ϊ�
	
	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;
	

	/**
	* �����蔻��
	*/
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {   // �X�e�[�W
			if (IsHitStage(*(*itr), 0.8f) == true) {
				modeGame->_objServer.Del(this);
			}
		}
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::RETICLE) { // ���`�N��
			if (IsHitScrnPos(*(*itr)) == true) {
				if (_canLockFlag) {
					if (trg & PAD_INPUT_2) {
						_bulletDir = -1.0f;   // �e���͂����Ԃ����
						_repelFlag = true;    // �e���Ԃ��ꂽ�̂Ńt���O�𗧂Ă�
						gGlobal._totalRepelCnt++;    // �e���Ԃ��񐔃J�E���g(�X�R�A�v�Z�p)
					}
				}
			}
		}
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) { // �{�X
			if (IsHitLineSegment(*(*itr), 10.0f) == true) {
				if (_repelFlag) {
					modeGame->_objServer.Del(this);
					(*itr)->Damage();
				}
			}
		}
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {  // �v���C���[
			if (IsDot(*(*itr)) == true && _camStateMLS) {
				_canLockFlag = true;
			}
			else {
				_canLockFlag = false;
			}
		}
	}
}

void BossBullet::Render(){

	float modelSize = 0.005f;
	MV1SetScale(_mh, VGet(modelSize, modelSize, modelSize));
	MV1SetPosition(_mh, _vPos);
	MV1SetRotationXYZ(_mh, VGet(0.f, (_shotAngle + 270.f) / 180.f * DX_PI_F, 0.f));
	MV1DrawModel(_mh);
	
	if (_canLockFlag) {
	//	DrawBox(_scrnPos.x + _hitX, _scrnPos.y + _hitY, _scrnPos.x + _hitW, _scrnPos.y + _hitH, GetColor(255, 0, 0), TRUE);
		if (_repelFlag) {
			DrawGraph(_scrnPos.x - 40.0f, _scrnPos.y - 35.0f, _cg[1], TRUE);
		}
		else {
			DrawGraph(_scrnPos.x - 40.0f, _scrnPos.y - 35.0f, _cg[0], TRUE);
		}
	}
	
//	DrawCapsule3D(_capsulePos1,_capsulePos2, 1.f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
	
//	DrawFormatString(0, 500, GetColor(255, 0, 0), "  �o�������e�̐�(size())  = %d", _lsBlt.size());
#if 0
	int y = 160;
	int size = 16;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "BossBullet:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  screenPos    = (%5.2f, %5.2f, %5.2f)", _scrnPos.x, _scrnPos.y, _scrnPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �o�������e�̐�(size())  = %d", _lsBlt.size());
	
#endif
}