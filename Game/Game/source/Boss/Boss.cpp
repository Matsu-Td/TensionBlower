/**
 * @file   Boss.cpp
 * @brief  �{�X�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "Boss.h"
#include "../Mode/ModeGame.h"

Boss* Boss::_pInstance = nullptr;

Boss::Boss(){

	_pInstance = this;

	_mh = MV1LoadModel("res/model/boss/Tboss_model_mm.mv1");
	_shadowModel = MV1LoadModel("res/model/boss/Tboss_model_mm_shadow.mv1");

	Initialize();
}

Boss::~Boss(){
	MV1DeleteModel(_mh);
}

/*
 * ������
 */
void Boss::Initialize() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	_vPos = VGet(0.0f, 0.0f, 0.0f);
	_vDir = VGet(0.0f, 0.0f, 0.0f);
	_attachIndex = 0;
	_totalTime = 0.0f;
	_state = STATE::NORMAL;
	_sinCnt = 0.0f;
	_angle = 90.0f / 180.0f * DX_PI_F;

	_attachIndex = -1;
	_totalTime = 0.0f;
	_playTime = 0.0f;

	_shotPattern = 1;
	_shotAngle = -90.0f;
	_shotAngle1 = -90.0f;
	_shotCnt = 1;
	_mlsCnt = 0;
	_reverseCnt = 60;
	_setRotAngle = 1.0f;
	_shotHeight = 0.0f;

	_hitpoint = modeGame->_charaData->_boss.maxHP;
	_shield = modeGame->_charaData->_boss.maxShield;
	_bulletNum = 0;
	_stateDown = false;
	_mlsDownFlag = false;
	_downTime = 0;
	_phase = 0;

	_deathCnt = 140;
	_deathFlag = false;

	_r = 10.0f;
}

/*
 * �t���[�������F�v�Z
 */
void Boss::Process(){

	// �J�����̏�Ԃ��擾
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	
	// �����O�̏�Ԃ�ۑ�
	_oldState = _state;

	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos1.y = _vPos.y + ADD_POS_Y;   // y���W(����)�̂݉��Z
	_capsulePos2 = _vPos;
	_capsulePos2.y = _vPos.y + ADD_POS_Y;   // y���W(����)�̂݉��Z

    // ���S����
	Death();

	// ���S������ȍ~�̏����͍s��Ȃ�
	if (_deathFlag) {
		return;
	}

	// ���A
	if (_state == STATE::RETURN) {
		if (_playTime == _totalTime) {
			_state = STATE::NORMAL;
		}
	}

	// �ʏ���
	if (_state == STATE::NORMAL) {
		// �{�X�̉�]���x�ؑ֗p
		float rotSpdChange = 1.0f;

		// �e���U������
		if (_shield > 0) {
			// �}���`���b�N�I���V�X�e���������͍s���ƒe�̔��ˑ��x��x������
			if (camState == Camera::STATE::MLS_LOCK) {
				_mlsCnt++;
				rotSpdChange = 0.01f;
				if (_mlsCnt % 100 == 0) {
					ShotPatternSwitch();
				}
			}
			// �ʏ펞
			else {
				_mlsCnt = 0;
				ShotPatternSwitch();
			}
		}
		// �{�X�̏㉺�^��
		_sinCnt += 1.0f * rotSpdChange;
		_vPos.y = 2.0f - sin(DX_PI_F / 90.0f * _sinCnt) * 2.0f;

		// �v���C���[����������Ƀ{�X�̐��ʂ�������
		DirectionalRotation(rotSpdChange);
		
	}

	// �t�F�[�Y�ؑ�
	FhaseChange();
	
	// �_�E������
	StateDown();

	// ���[�V�����ؑ�
	MotionSwitch();
}

/*
 * �t���[�������F�`��
 */
void Boss::Render(){

	ObjectBase::ShadowRender();

	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetPosition(_mh, _vPos);
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(_vDir.x, _vDir.z);
	MV1SetRotationXYZ(_mh, vRot);
	MV1DrawModel(_mh);

#ifdef _DEBUG
	int y = 750;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Boss:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos     = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dir     = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  cross     = (%5.2f, %5.2f, %5.2f)", _cross.x, _cross.y, _cross.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP�@    = %d", _hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ����ޒl = %d", _shield);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �o�����Ă���e�̐� = %d", _bulletNum);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_�E������ = %d", _downTime);   y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  _vDir.y = %f", _vDir.y); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ��� = %d", _state); y += size;
	DrawCapsule3D(_capsulePos1, _capsulePos2, 10.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}