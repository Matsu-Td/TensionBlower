/**
 * @file   Player.cpp
 * @brief  �v���C���[�֘A����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Player.h"
#include "Camera.h"
#include "Boss.h"
#include "BossBullet.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "Reticle.h"
#include "Sound.h"
#include "PlayerVoice.h"
#include "HitEffect.h"

Player* Player::_pInstance = NULL;

Player::Player(){

	_pInstance = this;
	_mh = MV1LoadModel("res/model/player/pl_model_mm.mv1");

	Initialize();
}

Player::~Player(){
	MV1DeleteModel(_mh);
}

/**
 * ������
 */
void Player::Initialize(){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	_vPos = VGet(0.0f, 0.0f, -115.0f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = CHARA_DATA->_mvSpdNorm;
	_attachIndex = -1;
	_totalTime = 0;
	_playTime = 0.0f;

	// �q�b�g�|�C���g
	_hitpoint = CHARA_DATA->_maxHP;

	// �W�����v
	_jumpTime = 0.0f;
	_canJump = true;

	// �_�b�V��
	_isDash = false;
	_isShortDash = false;
	_canLongDash = false;

	// �G�l���M�[
	_energy = CHARA_DATA->_maxEnergy;
	_isCharging = false;
	_canAutoCharge = true;
	_autoChargeCnt = 30;

	// �ߐڍU��
	_isAttack = false;
	_attackCnt = 0;
	_attackReloadTime = 0;
	_receptionTime = 0;
	_hitFlag = false;
	_canHitFlag = false;

	// �Q�[���I�[�o�[
	_gameOverCnt = 160;
	_isGameOver = false;

	// ���̑�
	_camStateMLS = false;

	// �e�ߐڍU���̃A�j���[�V�������Đ����Ԃ��i�[
	for (int i = 0; i < ATTACK_NUM; i++) {
	_attackTotalTime[_attackString[i]] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, _attackTchar[i])));
	}
}

/**
 * �����蔻��
 */
void Player::Collision() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		// �X�e�[�W�Ƃ̓����蔻��(�ǂ���)
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {
			if (IsHitStage(*(*itr), 2.0f) == true) {
				VECTOR slideVec;
				slideVec = VCross(_vDir, (*itr)->_hitPolyDim.Dim->Normal);
				slideVec = VCross((*itr)->_hitPolyDim.Dim->Normal, slideVec);
				_vPos = VAdd(_oldPos, slideVec);
     			MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);

				while (1) {
					// �J�v�Z���ʒu�X�V
					_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
					_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

					if (IsHitStage(*(*itr), 2.0f) == false) { break; }

					_vPos = VAdd(_vPos, VScale((*itr)->_hitPolyDim.Dim->Normal,0.001f));
					MV1CollResultPolyDimTerminate((*itr)->_hitPolyDim);
				}
			}
				}
		// �{�X�̒e�Ƃ̓����蔻��
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
			// ���e
			if (IsHitLineSegment(*(*itr), (*itr)->_r)) {
				modeGame->_objServer.Del(*itr);
				if (_hitpoint > 0) {
					int voiceNo = rand() % 2;
					if (voiceNo == 0) {
						PlaySoundMem(gPlayerVoice._vc["hidan"], DX_PLAYTYPE_BACK);
					}
					else {
						PlaySoundMem(gPlayerVoice._vc["hukki"], DX_PLAYTYPE_BACK);
					}
					PlaySoundMem(gSound._se["hit_player"], DX_PLAYTYPE_BACK);
					_hitpoint -= CHARA_DATA->_boss.shotDmg;
				}
			}
			// �J�X������(�G�l���M�[��)
			if (IsHitLineSegment(*(*itr), 2.5f)) {
				if (_energy < CHARA_DATA->_maxEnergy) {
					_energy += CHARA_DATA->_egAvoid;
				}
				gGlobal._totalGetEnergy += CHARA_DATA->_egAvoid;
			}
			if (Boss::GetInstance()->_mlsDownFlag) {
				modeGame->_objServer.Del(*itr);
			}
		}
		// �{�X�Ƃ̓����蔻��
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) {
			if (IsHitArc_Sphere(*(*itr)) == true) {
				if (_canHitFlag && !_hitFlag) {
					_hitFlag = true;
					_bossDamageCall->AttackDamage(Boss::GetInstance());
					VECTOR tmpPos = MV1GetFramePosition(_mh, MV1SearchFrame(_mh, "weapon3"));
					// �q�b�g�G�t�F�N�g����
					HitEffect* hitEffect = NEW HitEffect(tmpPos);
					modeGame->_objServer.Add(hitEffect);
				}
			}
			if (IsHitLineSegment(*(*itr), (*itr)->_r)) {
				_vPos = VAdd(_vPos, VScale(_oldPos, 0.4f));
			}
		}
		// ���[�U�[�Ƃ̓����蔻��
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::LASER) {
			if (IsHitLineSegment(*(*itr),(*itr)->_r) == true) {
				_hitpoint -= 5;
			}
		}
	}

	// HP�����l�ێ�
	if (_hitpoint <= 0) {
		_hitpoint = 0;
	}
}

/**
 * �t���[�������F�v�Z
 */
void Player::Process(){

	// �L�[�̎擾
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ���[�h�Q�[���擾
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// �����蔻��p�J�v�Z�����
	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

	// �A�i���O�X�e�B�b�N�Ή�
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);

	// �Q�[���p�b�h�uRT�v
	int rt = dinput.Z;
	// ���A�i���O�X�e�B�b�N���W
	float lx, ly;   
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// �����O�̃X�e�[�^�X��ۑ�
	STATE oldState = _state;

	// �����O�̈ʒu��ۑ�
	_oldPos = _vPos;

	// �{�X�f�[�^�擾
	{
		VECTOR bsPos = Boss::GetInstance()->GetPos();
		float dx = _vPos.x - bsPos.x;
		float dz = _vPos.z - bsPos.z;
		float len = sqrt(dx * dx + dz * dz);
		_bsAngle = atan2(dz, dx);
		if (len <= 50) {
			_isNearBoss = true;
		}
		else {
			_isNearBoss = false;
		}
	}

	// �J�����f�[�^�擾
	VECTOR camPos = Camera::GetInstance()->GetPos();      // �J�����ʒu
	VECTOR camTarg = Camera::GetInstance()->GetTarg();    // �J�����̒����_
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();  // �J�����̏��



	// �J�����̌����Ă���p�x�擾
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// �ړ����������߂�
	VECTOR vec = { 0.0f,0.0f,0.0f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);

	// �Q�[���I�[�o�[����
	if (_isGameOver) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = new ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}
	// �q�b�g�|�C���g 0 �ŃQ�[���I�[�o�[
	if (_hitpoint <= 0) { 
		_state = STATE::DEAD;
		_isGameOver = true;
	}

	// ���S���[�V�����͒n��ōs��
	if (_state == STATE::DEAD) {
		// �d�͏���
		_vPos.y -= GRAVITY;
		if (_vPos.y < 0.0f) {
			_vPos.y = 0.0f;
		}
	}

	// �ړ�����
	if (length < ANALOG_MIN) {
		length = 0.0f;
	}
	else {
		length = _mvSpd;
	}

	// TODO: �J�����̎d�l�ύX(�f�t�H���g�����b�N��ԂɂȂ���)�ɂ��v���C���[�̈ړ������̌��������K�v
	// �}���`���b�N�V�X�e�����������Ă��Ȃ��Ƃ��͈ړ��\
	if (camState != Camera::STATE::MLS_LOCK && !_isAttack && !_isGameOver) {
		// vec��rad����]������
		vec.x = cos(rad + camRad) * length;
		vec.z = sin(rad + camRad) * length;

		// vec�̕��ړ�
		_vPos = VAdd(_vPos, vec);

		// �ړ��ʂ����̂܂܃L�����̌����ɂ���
		if (VSize(vec) > 0.0f) {		// �ړ����Ă��Ȃ����͖�������
			if (camState == Camera::STATE::TARG_LOCK_ON){
				_vDir.x = -cos(_bsAngle);
                _vDir.z = -sin(_bsAngle);
				_dashCall->LeftAnalogDeg(this, length);
				
				if (!_isDash) {
					_mvSpd = CHARA_DATA->_mvSpdNorm;
				}				
			}
			else {
				_vDir = vec;
				if (_state != STATE::FOR_DASH) {
					_mvSpd = CHARA_DATA->_mvSpdNorm;
				}
				if (_canJump) {
					_state = STATE::WALK;
				}
			}
		}
		else if (_canJump && !_isAttack) {
			_state = STATE::WAIT;

		}
		// �d�͏���
		_vPos.y -= GRAVITY;
		if (_vPos.y < 0.0f) {
			_vPos.y = 0.0f;
		}

		// �W�����v
		_JumpCall->JumpAction(this);
		
		// ���݂̃v���C���[�̐��ʊp�x
		float nowAngle = atan2(_vDir.z, _vDir.x);

		// �_�b�V������
		_dashCall->Dash(this, nowAngle, length);

		// �G�l���M�[����
		if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5)&& _energy < CHARA_DATA->_maxEnergy) {
			if (_state != STATE::JUMP) {  // �W�����v���ĂȂ���Η��߉\
				if (!_isDash) {           // �_�b�V�����ĂȂ���Η��߉\
					_mvSpd = CHARA_DATA->_mvSpdChrg;
					_isCharging = true;
				}
			}
		}
		else {
			_isCharging = false;
		}

		// �ߐڍU��(����̂�)
		if (_vPos.y == 0.0f) {
			_attackCall->FirstAttack(this);
		}
	}

    // �ߐڍU������(2���ڈȍ~)
	_attackCall->SecondAttack(this);

	if (_camStateMLS) {
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		_state = STATE::NONE;
	}
		
	// �}���`���b�N�V�X�e���p�Ə��ǉ�
	if (trg & PAD_INPUT_5) {
		_camStateMLS = true;
		Reticle* reticle = NEW Reticle();
		modeGame->_objServer.Add(reticle);
	}
	else {
		_camStateMLS = false;
	}

	// �G�l���M�[�Ǘ�
	_energyCall->EnergyManager(this, oldState);

	// �����蔻��
	Collision();

	// ���f�����[�V�����ؑ�
	_motionCall->SwitchMotion(this, oldState);

	// �c��HP�ۑ�(�X�R�A�v�Z�p)
	gGlobal._remainingHP = _hitpoint;
}

/**
 * �t���[�������F�`��
 */
void Player::Render(){

    MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	{
		MV1SetPosition(_mh, _vPos);
		// ��������Y����]���Z�o
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);
		MV1SetRotationXYZ(_mh, vRot);
		MV1DrawModel(_mh);
	}

#if 0  // �f�o�b�O�p
	float angle = atan2(_vDir.z ,_vDir.x);
	float deg = angle * 180.f / DX_PI_F;
	int x = 100;
	int y = 340;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Player:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dir    = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  deg    = %5.1f", deg); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  spd    = %3.1f", _mvSpd); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  charge = %d", _isCharging); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dash   = %d", _isDash); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ��ST�p�x = %d", _lfAnalogDeg); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP     = %d", _hitpoint); y += size;

	DrawFormatString(0, y, GetColor(255, 0, 0), "  �U���J�E���g = %d", _attackCnt); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �U����t���� = %d", _receptionTime); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �U���۰�ގ��� = %d", _attackReloadTime); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_���[�WHP = %d", _nowDmgHP); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_���[�WSLD= %d", _nowDmgSld); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �_���[�W�ʏ� = %d", _nowDmgNorm); y += size;
	DrawString(0, y, "�@��ԁF",GetColor(255, 0, 0));
	switch (_state) {
	case STATE::WAIT:
		DrawString(x, y, "WAIT", GetColor(255, 0, 0)); break;
	case STATE::WALK:
		DrawString(x, y, "WALK", GetColor(255, 0, 0)); break;
	case STATE::FOR_DASH:
		DrawString(x, y, "FOR DASH", GetColor(255, 0, 0)); break;
	case STATE::JUMP:
		DrawString(x, y, "JUMP", GetColor(255, 0, 0)); break;
	case STATE::LEFT_MOVE:
		DrawString(x, y, "LEFT MOVE", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_MOVE:
		DrawString(x, y, "RIGHT MOVE", GetColor(255, 0, 0)); break;
	case STATE::BACK_MOVE:
		DrawString(x, y, "BACK MOVE", GetColor(255, 0, 0)); break;
	case STATE::LEFT_DASH:
		DrawString(x, y, "LEFT DASH", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_DASH:
		DrawString(x, y, "RIGHT DASH", GetColor(255, 0, 0)); break;
	case STATE::BACK_DASH:
		DrawString(x, y, "BACK DASH", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK1:
		DrawString(x, y, "WEAK ATTACK1", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK2:
		DrawString(x, y, "WEAK ATTACK2", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK3:
		DrawString(x, y, "WEAK ATTACK3", GetColor(255, 0, 0)); break;
	case STATE::WEAK_ATCK4:
		DrawString(x, y, "WEAK ATTACK4", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK1:
		DrawString(x, y, "STRG ATTACK1", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK2:
		DrawString(x, y, "STRG ATTACK2", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK3:
		DrawString(x, y, "STRG ATTACK3", GetColor(255, 0, 0)); break;
	case STATE::STRG_ATCK4:
		DrawString(x, y, "STRG ATTACK4", GetColor(255, 0, 0)); break;
	}

#endif
}

void Player::ExplosionDamage(){
	
	if (_hitpoint > 0) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		_hitpoint -= CHARA_DATA->_boss.exolosionDmg;
	}
}
