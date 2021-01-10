
#include "ApplicationMain.h"
#include "Player.h"
#include "Camera.h"
#include "Boss.h"

Player* Player::_pInstance = NULL;

Player::Player()
{
	_pInstance = this;
	_mh = ResourceServer::MV1LoadModel("res/model/仮データ/SDChar/SDChar.mv1");;
	_mhMap = MV1LoadModel("res/model/仮データ/stage_dummy02.mv1");

	MV1SetupCollInfo(_mhMap, -1, 16, 16, 16);
	Initialize();
}

Player::~Player()
{

}

void Player::Initialize()
{
	_vPos = VGet(0.f, 0.f, -115.f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = NOR_MV_SPD;
	_attachIndex = -1;
	_totalTime = 0;
	_playTime = 0.f;
	_jumpTime = 0.f;
	_isCanJump = true;
	_isCharging = false;
	_isShortDash = false;
	_isDash = false;
}

void Player::JumpAction() 
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
		_state = STATE::JUMP;
		_isCanJump = false;
		_mvSpd = NOR_MV_SPD;
		_jumpTime = 0.f;
	}
	if (!_isCanJump) {
		float gravity = 0.9f;
		float inVel = 4.f;
		_vPos.y = inVel * _jumpTime - 0.5f * gravity * _jumpTime * _jumpTime;
	}
	_jumpTime += 0.2f;

	if (_vPos.y < GROUND_Y) {
		_vPos.y = GROUND_Y;
		if (_isCharging == false) {
			_isCanJump = true;
		}
	}
}

void Player::LeftAnalogDeg(float length)
{
	if (_isCanJump) {
		if (_isDash) {
			_mvSpd = DASH_MV_SPD;
			if (_lfAnalogDeg >= 120 || _lfAnalogDeg <= -120) {
				_state = STATE::FOR_DASH;
			}
			else if (_lfAnalogDeg < -45 && _lfAnalogDeg > -120) {
				_state = STATE::LEFT_DASH;
			}
			else if (_lfAnalogDeg > 45 && _lfAnalogDeg < 120) {
				_state = STATE::RIGHT_DASH;
			}
			else if (_lfAnalogDeg >= -45 && _lfAnalogDeg <= 45 && length >= 0.3f) {
				_state = STATE::BACK_DASH;
			}
			else {
				_state = STATE::FOR_DASH;  // 入力がRBのみ
			}
		}
		else {
			_mvSpd = NOR_MV_SPD;
			if (_lfAnalogDeg >= 120 || _lfAnalogDeg <= -120) {
				_state = STATE::WALK;
			}
			else if (_lfAnalogDeg < -45 && _lfAnalogDeg > -120) {
				_state = STATE::LEFT_MOVE;
			}
			else if (_lfAnalogDeg > 45 && _lfAnalogDeg < 120) {
				_state = STATE::RIGHT_MOVE;
			}
			else if (_lfAnalogDeg >= -45 && _lfAnalogDeg <= 45) {
				_state = STATE::BACK_MOVE;
			}
		}
	}
}

void Player::Process()
{
	_oldPos = _vPos;
	// キーの取得
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// 当たり判定用カプセル情報
	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 4.f, _vPos.z);

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;           // 左アナログスティックの座標
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// 処理前のステータスを保存しておく
	STATE oldState = _state;

	// カメラデータ取得
	VECTOR camPos = Camera::GetInstance()->GetPos();
	VECTOR camTarg = Camera::GetInstance()->GetTarg();
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// ボスデータ取得
	VECTOR bsPos = Boss::GetInstance()->GetPos();
	{
		float dx = _vPos.x - bsPos.x;
		float dz = _vPos.z - bsPos.z;
		_bsAngle = atan2(dz, dx);
	}

	// カメラの向いている角度取得
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// 移動方向を決める
	VECTOR vec = { 0.f,0.f,0.f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);

	if (length < analogMin) {
		length = 0.f;
	}
	else {
		length = _mvSpd;
	}

	if (camState != Camera::STATE::MLS_LOCK) {  // マルチロックシステムが発動していないときは移動可能
		// vecをrad分回転させる
		vec.x = cos(rad + camRad) * length;
		vec.z = sin(rad + camRad) * length;

		// vecの分移動
		_vPos = VAdd(_vPos, vec);

		// 移動量をそのままキャラの向きにする
		if (VSize(vec) > 0.f) {		// 移動していない時は無視するため
			if (camState == Camera::STATE::TARG_LOCK_ON){
				_vDir.x = -cos(_bsAngle);
                _vDir.z = -sin(_bsAngle);
				LeftAnalogDeg(length);
				
				if (!_isDash) {
					_mvSpd = NOR_MV_SPD;
				}
				
			}
			else {
				_vDir = vec;
				if (_state != STATE::FOR_DASH) {
					_mvSpd = NOR_MV_SPD;
				}
				if (_isCanJump) {
					_state = STATE::WALK;
				}
			}
		}
		else if (_isCanJump) {
			_state = STATE::WAIT;

		}

		/**
		* ジャンプ
		*/
		JumpAction();

		/**
        * 短押しダッシュ
        */
		float nowAngle = atan2(_vDir.z, _vDir.x);  // 現在のプレイヤーの正面角度
		VECTOR vDash{ 0.f,0.f,0.f };               // ダッシュする方向
		if (trg & PAD_INPUT_6 && (_state != STATE::JUMP)) {
			_mvSpd = DASH_MV_SPD;
			_isShortDash = true;
			_dashCnt = 10;
		}
		if (_isShortDash) {
			_dashCnt--;
			if (_dashCnt > 0) {
				_isDash = true;
				if (camState != Camera::STATE::TARG_LOCK_ON) {
					_state = STATE::FOR_DASH;
				}
				_isCharging = false;
				if (length < analogMin) {
					if (camState == Camera::STATE::TARG_LOCK_ON) {
						LeftAnalogDeg(length);
						vDash.x = -cos(_bsAngle) * _mvSpd;
						vDash.z = -sin(_bsAngle) * _mvSpd;
					}
					else {
						vDash.x = cos(nowAngle) * _mvSpd;
						vDash.z = sin(nowAngle) * _mvSpd;
					}
					_vPos.x += vDash.x;
					_vPos.z += vDash.z;
				}
			}
			else {
				_dashCnt = 0;
				_isShortDash = false;
				_isDash = false;
			}
		}
		/**
		* 長押しダッシュ
		*/
		if (key & PAD_INPUT_6) {		
			if (_isCanJump && !_isShortDash) {
				_isDash = true;
				if (camState != Camera::STATE::TARG_LOCK_ON) {
					_state = STATE::FOR_DASH;
				}
				_isCharging = false;
				if (length < analogMin) {
					if (camState == Camera::STATE::TARG_LOCK_ON) {
						LeftAnalogDeg(length);
						vDash.x = -cos(_bsAngle) * _mvSpd;
						vDash.z = -sin(_bsAngle) * _mvSpd;
						_vPos.x += vDash.x;
						_vPos.z += vDash.z;
					}
					else {
						vDash.x = cos(nowAngle) * _mvSpd;
						vDash.z = sin(nowAngle) * _mvSpd;
						_vPos.x += vDash.x;
						_vPos.z += vDash.z;
					}
				}
			}
		}
		else {
			_isDash = false;
		}
		/**
		* エネルギー溜め
		*/
		if (key & PAD_INPUT_3) {
			if (_state != STATE::JUMP) {  // ジャンプしてなければ溜め可能
				if (_state != STATE::FOR_DASH) {
					_mvSpd = CHARGE_MV_SPD;
					_isCharging = true;
				}
			}
		}
		else {
			_isCharging = false;
		}
	}
	/**
	* 壁との当たり判定、壁ずり
	*/
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
	_hitPolyDim = MV1CollCheck_Capsule(_mhMap, -1, _capsulePos1, _capsulePos2, 2.f);
	
	if (_hitPolyDim.HitNum >= 1) {	
		VECTOR slideVec;
		slideVec = VCross(vec, _hitPolyDim.Dim->Normal);
		slideVec = VCross(_hitPolyDim.Dim->Normal, slideVec);
		_vPos = VAdd(_oldPos, slideVec);
		_vPos = VAdd(_vPos, VScale(_hitPolyDim.Dim->Normal, 0.03f));
	}

	if (oldState == _state) {
		_playTime += 0.5f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
		}
		switch (_state) {
		case STATE::WAIT:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "idle"), -1, FALSE);
			break;
		case STATE::WALK:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "run"), -1, FALSE);
			break;
		case STATE::JUMP:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::FOR_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::LEFT_MOVE:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::RIGHT_MOVE:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::BACK_MOVE:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::LEFT_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::RIGHT_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		case STATE::BACK_DASH:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, ""), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);
	
		_playTime = 0.0f;
	}

	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}

	MV1CollResultPolyDimTerminate(_hitPolyDim);

	// 射撃
	_bullet.Process();
}

void Player::Render()
{
	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(0.05f, 0.05f, 0.05f));
	{
		MV1SetPosition(_mh, _vPos);
		// 向きからY軸回転を算出
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);		// モデルが標準でどちらを向いているかで式が変わる(これは-zを向いている場合)
		MV1SetRotationXYZ(_mh, vRot);
		MV1DrawModel(_mh);
	}
	// 射撃
	_bullet.Render();

#if 1
	float angle = atan2(_vDir.x * -1, _vDir.z * -1);
	float deg = angle * 180.f / DX_PI_F;
	int y = 125;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Player:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dir    = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  deg    = %5.1f", deg); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  spd    = %3.1f", _mvSpd); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  charge = %d", _isCharging); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dash   = %d", _isDash); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  左ST角度 = %d", _lfAnalogDeg); y += size;
	switch (_state) {
	case STATE::WAIT:
		DrawString(0, y, "　状態：WAIT", GetColor(255, 0, 0)); break;
	case STATE::WALK:
		DrawString(0, y, "　状態：WALK", GetColor(255, 0, 0)); break;
	case STATE::FOR_DASH:
		DrawString(0, y, "　状態：FOR DASH", GetColor(255, 0, 0)); break;
	case STATE::JUMP:
		DrawString(0, y, "　状態：JUMP", GetColor(255, 0, 0)); break;
	case STATE::LEFT_MOVE:
		DrawString(0, y, "　状態：LEFT MOVE", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_MOVE:
		DrawString(0, y, "　状態：RIGHT MOVE", GetColor(255, 0, 0)); break;
	case STATE::BACK_MOVE:
		DrawString(0, y, "　状態：BACK MOVE", GetColor(255, 0, 0)); break;
	case STATE::LEFT_DASH:
		DrawString(0, y, "　状態：LEFT DASH", GetColor(255, 0, 0)); break;
	case STATE::RIGHT_DASH:
		DrawString(0, y, "　状態：RIGHT DASH", GetColor(255, 0, 0)); break;
	case STATE::BACK_DASH:
		DrawString(0, y, "　状態：BACK DASH", GetColor(255, 0, 0)); break;
	}
	DrawCapsule3D(_capsulePos1, _capsulePos2, 2.f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}

/* 他ファイルからの変数値を持ってくる方法例
//VECTOR _cam = Camera::GetInstance()-GetPos();
	//ModeGame* modegame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	//printfDx("%f\n", _cam);

		// シングルトン実装例
	VECTOR camPos = Camera::GetInstance()->GetPos();
	DrawFormatString(0, 100, GetColor(255, 0, 0), "  camPos.x = %5.2f", camPos.x);
	DrawFormatString(0, 120, GetColor(255, 0, 0), "  camPos.y = %5.2f", camPos.y);
	DrawFormatString(0, 140, GetColor(255, 0, 0), "  camPos.z = %5.2f", camPos.z);
*/