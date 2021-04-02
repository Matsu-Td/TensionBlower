/**
 * @file   Boss.cpp
 * @brief  �{�X�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/14
 */

#include "Boss.h"
#include "../Mode/ModeGame.h"
#include "../Application/ApplicationMain.h"
#include "../Player/Player.h"
#include "../Mode/ModeGameClear.h"
#include "BossBullet.h"
#include "BossBomb.h"
#include "BossAimShot.h"
#include "../Sound/Sound.h"
#include "../Effect/Destruction.h"
#include "BossVoice.h"
#include "../Effect/Laser.h"

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

/**
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

	_deadCnt = 140;
	_deadFlag = false;

	_r = 10.0f;
}

/**
 * ���f�[�^�Đ�
 */
void Boss::PlayVoice(std::string voiceName) {
	PlaySoundMem(gBossVoice._vc[voiceName], DX_PLAYTYPE_BACK);
}

/**
 * 6��ނ̐��f�[�^�������_���ŗ���
 */
void Boss::PlayAttackVoiceChange() {

	int voiceNo = rand() % ATTACK_VOICE_NUM;
	PlayVoice(_attackNameNo[voiceNo]);
}

/**
 * �t�F�[�Y�ύX����
 */
void Boss::FhaseChange() {

	// �t�F�[�Y4�ֈڍs
	if (_hitpoint <= PHASE_FOUR_HP) {
		_phase = 4;
		return;
	}
	// �t�F�[�Y3�ֈڍs
	if (_hitpoint <= PHASE_THREE_HP) {
		_phase = 3;
		return;
	}
	// �t�F�[�Y2�ֈڍs
	if (_hitpoint <= PHASE_TWO_HP) {
		_phase = 2;
		return;
	}
	// �t�F�[�Y1�ֈڍs
	if (_hitpoint <= PHASE_ONE_HP) {
		_phase = 1;
		return;
	}
	// �����t�F�[�Y0
	_phase = 0;
}

/**
 * �_�E����ԏ���
 */
void Boss::StateDown(){

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// ���A
	if (_state == STATE::DOWN) {
		_vPos.y = 0.0f;
		_mlsDownFlag = false;	   // �}���`���b�N�I���V�X�e���ɂ��_�E���t���O����
		_downTime--;               // �_�E�����ԃJ�E���g
		if (_downTime < 0) {
			// ���A���̐��f�[�^�Đ�
			PlayVoice("hukki");
			_downTime = 0;         // �_�E�����ԃ��Z�b�g
			_state = STATE::RETURN;// ���A��Ԃɂ�����
			_bulletNum = 0;        // �e�̐����Z�b�g
			_shield = modeGame->_charaData->_boss.maxShield;  // �V�[���h�l�S��
		}
	}

	if (_shield > 0) {
		return;
	}
	// �_�E��
	if (_state == STATE::NORMAL) {
		PlaySoundMem(gSound._se["down"], DX_PLAYTYPE_BACK);
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
				_bulletNum++;   // �_�E�����O�ɏo�����Ă����e�̐����J�E���g
			}
			int plEnergy = Player::GetInstance()->GetEnergy();            // �v���C���[�̃G�l���M�[���擾
			_downTime = MIN_DOWN_TIME + plEnergy / 20 + _bulletNum;       // �_�E�����Ԍv�Z                                           // �_�E����Ԃɂ���
			_state = STATE::DOWN;
		}
	}
}

/**
 * �Q�[���N���A����
 */
void Boss::Dead() {

	// �Q�[���N���A�����X�^�[�g
	if (_deadFlag) {
		_deadCnt--;
		if (_deadCnt == 0) {
			MV1DeleteModel(_mh); // �{�X���f�����폜����
		}
	}
	// �q�b�g�|�C���g�[���ŃQ�[���N���A�t���O�𗧂Ă�
	if (_hitpoint <= 0) {
		if (!_deadFlag) {
			// ���j���̐��f�[�^�Đ�
			PlayVoice("gekiha");
			VECTOR tmpPos = _vPos;
			tmpPos.y = 8.5f;
			Destruction* destruction = NEW Destruction(tmpPos);
			ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
			modeGame->_objServer.Add(destruction);

		}
		_hitpoint = 0;
		_deadFlag = true;
	}
}

/**
 * ���[�V�����ؑ�
 */
void Boss::MotionSwitch(STATE oldState) {

	if (oldState == _state) {
		_playTime += 1.0f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
		}
		switch (_state) {
		case STATE::NORMAL:
			_attachIndex = -1; // �ʏ�̓��[�V��������
			break;
		case STATE::DOWN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "down"), -1, FALSE);
			break;
		case STATE::RETURN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "return"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}
}

/**
 * �{�X���ʕ�����]����
 */
void Boss::DirectionalRotation(float rotSpdChenge) {

	// �v���C���[�̈ʒu���擾
	VECTOR plPos = Player::GetInstance()->GetPos();

	// �{�X�̃t�H���[�h�x�N�g��
	VECTOR forward = { cos(_angle),0.0f,sin(_angle) };

	// �v���C���[�Ɍ������x�N�g��
	VECTOR dis = VSub(plPos, _vPos);
	// �P�ʃx�N�g����
	dis = VNorm(dis);

	// �O�ςŃv���C���[�̈ʒu�����E���肵�A�{�X�̌�������]������
	_cross = VCross(forward, dis);
	if (_cross.y > 0.0f) {
		_angle += ROT_SPD * rotSpdChenge;
	}
	else if (_cross.y < 0.0f) {
		_angle -= ROT_SPD * rotSpdChenge;
	}
	_vDir = { cos(_angle),0.0f,sin(_angle) };
}

/**
 * �t���[�������F�v�Z
 */
void Boss::Process(){

	// �J�����̏�Ԃ��擾
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	
	STATE oldState = _state;

	// ���S����
	Dead();

	if (_deadFlag) {
		return;
	}
	// �����蔻��p�J�v�Z��
	_capsulePos1 = _vPos;
	_capsulePos1.y = _vPos.y + ADD_POS_Y;   // y���W(����)�̂݉��Z
	_capsulePos2 = _vPos;
	_capsulePos2.y = _vPos.y + ADD_POS_Y;   // y���W(����)�̂݉��Z

	// ���A���
	if (_state == STATE::RETURN) {
		if (_playTime == _totalTime) {
			_state = STATE::NORMAL;
		}
	}

	// �ʏ���
	if (_state == STATE::NORMAL) {
		// �{�X�̉�]���x�ؑ֗p
		float rotSpdChenge = 1.0f;

		// �e���U������
		if (_shield > 0) {
			// �}���`���b�N�I���V�X�e���������͒e�̔��ˑ��x��x������
			if (camState == Camera::STATE::MLS_LOCK) {
				_mlsCnt++;
				rotSpdChenge = 0.01f;
				if (_mlsCnt % 100 == 0) {
					_patternCall->ShotPatternSwitch(this);
				}
			}
			// �ʏ펞
			else {
				_mlsCnt = 0;
				_patternCall->ShotPatternSwitch(this);
			}
		}
		// �{�X�̏㉺�^��
		_sinCnt += 1.0f * rotSpdChenge;
		_vPos.y = 2.0f - sin(DX_PI_F / 90.0f * _sinCnt) * 2.0f;

		// �v���C���[����������Ƀ{�X�̐��ʂ�������
		DirectionalRotation(rotSpdChenge);
		
	}

	// �t�F�[�Y�ؑ�
	FhaseChange();
	
	// �_�E������
	StateDown();

	// ���[�V�����ؑ�
	MotionSwitch(oldState);
}

/**
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