
#include "ApplicationMain.h"
#include "Player.h"
#include "Camera.h"
#include "Boss.h"
#include "BulletServer.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "Reticle.h"

Player* Player::_pInstance = NULL;

Player::Player()
{
	_pInstance = this;
	_mh = ResourceServer::MV1LoadModel("res/model/仮データ/SDChar/SDChar.mv1");;

	Initialize();
}

Player::~Player()
{

}

void Player::Initialize()
{
	_vPos = VGet(0.0f, 0.0f, -115.0f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = NOR_MV_SPD;
	_attachIndex = -1;
	_totalTime = 0;
	_playTime = 0.0f;
	_jumpTime = 0.0f;
	_isCanJump = true;
	_isCharging = false;
	_isShortDash = false;
	_isCanLongDash = false;
	_isDash = false;

	// 以下ステータス等
	//射撃
	_status.bulletNum = MAX_BULLET;
	_canShotFlag = true;
	_shotInterval = 5;
	_reloadTime = 90;
	_shotZeroFlag = false;

	//エネルギー
	_status.energy = MAX_ENERGY;
	_atChargeFlag = true;
	_atChargeCnt = 30;

	//ヒットポイント
	_status.hitpoint = MAX_HP;

	_gameOverCnt = 0;

	_camStateMLS = false;

	_swCharge = true;
}

void Player::JumpAction() 
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (_status.energy >= JUMP_ENERGY) {
		if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
			_state = STATE::JUMP;
			_isCanJump = false;
			_mvSpd = NOR_MV_SPD;
			_jumpTime = 0.f;
		}
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

void Player::EnergyManager(STATE oldState)
{
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	if (oldState != _state) { 
		// ジャンプ(消費)
		if (_state == STATE::JUMP) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
			_status.energy = _status.energy - JUMP_ENERGY;
		}
		// 短押しダッシュ(消費)
		if (_isShortDash) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
			_status.energy = _status.energy - DASH_ENERGY;
		}
	}

	// 長押しダッシュ(消費)
	if(!_isShortDash && _isDash) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
		_status.energy--;
	}

	// マルチロックオンシステム
	if (camState == Camera::STATE::MLS_LOCK) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
		_status.energy -= 12.5;
	}
	//　溜め(回復)
	if (_isCharging) {
		_atChargeCnt = AT_CHARGE_CNT;
		_status.energy += AT_CHARGE * 2.5;
	}


	// 自動回復開始のインターバル
	if (!_atChargeFlag) {
		_atChargeCnt--;
		if (_atChargeCnt <= 0){   // 一定の自動回復開始間隔を設ける
			_atChargeCnt = 0;
			_atChargeFlag = true;
		}
	}
	// 自動回復
	else if (!_isCharging){
		_status.energy += AT_CHARGE;
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
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 5.f, _vPos.z);

	// カスリ判定用カプセル情報
//	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
//	_capsulePos2 = VGet(_vPos.x, _vPos.y + 5.f, _vPos.z);

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;           // 左アナログスティックの座標
	int rt = dinput.Z;    // ゲームパッド「RT」
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

	/**
	* ゲームオーバー処理
	*/
	if (_gameOverCnt > 0) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = new ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}

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
		if (trg & PAD_INPUT_6 && (_state != STATE::JUMP) && _status.energy > DASH_ENERGY) {
			_mvSpd = DASH_MV_SPD;
			_isShortDash = true;             // 短押しダッシュ移動スタート
			_isCanLongDash = true;           // 短押しダッシュ発動 ⇒ 長押しダッシュ発動可能となる
			_shortDashTime = SHORT_DASH_CNT;  // 短押しダッシュ移動時間をセット
			
		}
		if (_isShortDash) {
			_shortDashTime--;
			if (_shortDashTime > 0) {
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
				_shortDashTime = 0;
				_isShortDash = false;
				_isDash = false;
			}
		}
		/**
		* 長押しダッシュ
		*/
		if (key & PAD_INPUT_6) {		
			//プレイヤーが地上にいる 、長押しダッシュ可能(短押しダッシュを行った時)、短押しダッシュ移動が終わっている、エネルギー0よりある
			if (_isCanJump && _isCanLongDash && !_isShortDash && _status.energy > 0) {
				_isDash = true;
				_isCharging = false;
				if (camState != Camera::STATE::TARG_LOCK_ON) {
					_state = STATE::FOR_DASH;
				}
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
			_isCanLongDash = false;
		}

		/**
		* エネルギーチャージ
		*/
		if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5)) {
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


		/**
		* 射撃攻撃 (ゲームパッドRTで射撃)
		*/
		if (rt < -100 && !_isCharging && !_shotZeroFlag) { // 溜め状態及び装弾数がゼロになった場合は射撃不可
			if (_status.bulletNum == 0) {
				_shotZeroFlag = true;      // 弾を打ち切ってしまうとフラグが立つ(= true) ⇒ 射撃不可
			}
			if (_status.bulletNum > 0) {
				if (_canShotFlag) {
					_reloadTime = 90;	   // リロード開始時間をセット
					_canShotFlag = false;
					_status.bulletNum--;
					ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
					PlayerBullet* bullet = new PlayerBullet();
					VECTOR tmp = _vPos;
					tmp.y = _vPos.y + 3.5;
					bullet->SetPos(tmp);
					modeGame->_objServer.Add(bullet);
				}
				else {
					_shotInterval--;
					if (_shotInterval == 0) {
						_canShotFlag = true;
						_shotInterval = 10;      // 一定の射撃間隔を設ける
					}
				}

			}
		}
		else {             // 射撃を行わなければリロード開始
			_reloadTime--;
			if (_shotZeroFlag) {            // 弾を打ち切った場合は即時リロード開始
				if (_status.bulletNum < MAX_BULLET) {
					_status.bulletNum++;
				}
			}
			else if (_reloadTime <= 0) {    // 弾が残っている状態かつリロード開始時間ゼロでリロード開始
				if (_status.bulletNum < MAX_BULLET) {
					_status.bulletNum++;
				}
			}

		}
		if (_status.bulletNum == MAX_BULLET) {
			_shotZeroFlag = false;          // リロード完了で_shotZeroFlag解除(= false)
		}
	}

/*	if (camState == Camera::STATE::MLS_LOCK) {
		_camStateMLS = true;
	}*/
	
		
	// マルチロックシステム用レチクル追加	
	if (trg & PAD_INPUT_5) {
		_camStateMLS = true;
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = new Reticle();
		modeGame->_objServer.Add(reticle);
	}



	/**
	* エネルギー管理
	*/
	if (_status.energy > 0 || _status.energy < MAX_ENERGY) {
		if (_swCharge) {               // デバッグ用
			EnergyManager(oldState);
		}
	}
	if (_status.energy < 0) {
		_status.energy = 0;
	}
	if (_status.energy > MAX_ENERGY) {
		_status.energy = MAX_ENERGY;
	}

	if (trg & PAD_INPUT_7) {
		if (_swCharge) {
			_swCharge = false;
		}
		else {
			_swCharge = true;
		}
	}
	/**
	* 当たり判定
	*/
	{
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {  // ステージ
				if (IsHitStage(*(*itr), 2.0f) == true) {
					VECTOR slideVec;
					slideVec = VCross(vec, (*itr)->_hitPolyDim.Dim->Normal);
					slideVec = VCross((*itr)->_hitPolyDim.Dim->Normal, slideVec);
					_vPos = VAdd(_oldPos, slideVec);
					_vPos = VAdd(_vPos, VScale((*itr)->_hitPolyDim.Dim->Normal, 0.03f));
				}
			}
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) { // ボスの弾
				// 着弾
				if (IsHitLineSegment(*(*itr), 1.0f)) {
					modeGame->_objServer.Del(*itr);
					_status.hitpoint -= 100;
					if (_status.hitpoint <= 0) {
						_gameOverCnt = 60;
					}
				}
				// カスリ判定
				if (IsHitLineSegment(*(*itr), 2.5f)) {
					_status.energy += 3;				
				}		
			}
		}
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

#if 1
//	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
//	VECTOR pl = modeGame->_pl->GetPos();
	float angle = atan2(_vDir.x * -1, _vDir.z * -1);
	float deg = angle * 180.f / DX_PI_F;
	int y = 140;
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
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP     = %d", _status.hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  energy = %d, ON(1) / OFF(0) = %d (BACKキーで切替)", _status.energy, _swCharge); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  装弾数 = %d", _status.bulletNum); y += size;
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
	DrawCapsule3D(_capsulePos1, _capsulePos2, 1.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
	DrawCapsule3D(_capsulePos1, _capsulePos2, 2.5f, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);
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

//MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
/*	_hitPolyDim = MV1CollCheck_Capsule(_mhMap, -1, _capsulePos1, _capsulePos2, 2.f);

	if (_hitPolyDim.HitNum >= 1) {
		VECTOR slideVec;
		slideVec = VCross(vec, _hitPolyDim.Dim->Normal);
		slideVec = VCross(_hitPolyDim.Dim->Normal, slideVec);
		_vPos = VAdd(_oldPos, slideVec);
		_vPos = VAdd(_vPos, VScale(_hitPolyDim.Dim->Normal, 0.03f));
	}*/