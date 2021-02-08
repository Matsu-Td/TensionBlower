
/**
 * @file  Player.cpp
 * @brief プレイヤー関連処理
 *
 * @date 2021-02-08
 */


#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "Player.h"
#include "Camera.h"
#include "Boss.h"
#include "BulletServer.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "Reticle.h"

Player* Player::_pInstance = NULL;

Player::Player(){
	_pInstance = this;
	_mh = MV1LoadModel("res/model/仮データ/TB_player_mm01.mv1");
	Initialize();
}


Player::~Player(){
}


void Player::Initialize(){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	_vPos = VGet(0.0f, 0.0f, -115.0f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = CHARA_DATA->_mvSpdNorm;
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
	_bulletNum = MAX_BULLET;
	_canShotFlag = true;
	_shotInterval = 5;
	_reloadTime = RELOAD_TIME;
	_shotZeroFlag = false;

	//エネルギー
	_energy = CHARA_DATA->_maxEnergy;
	_atChargeFlag = true;
	_atChargeCnt = 30;

	//ヒットポイント
	_hitpoint = CHARA_DATA->_maxHP;

	_gameOverCnt = 60;
	_gameOverFlag = false;

	_camStateMLS = false;

	_swCharge = true;

	_shotFlag = false;

	_attackFlag = false;
	_receptionTime = 0;
	_attackReloadTime = 0;
	_hitFlag = false;
	_canHitFlag = false;

	_attackCnt = 0;

	_attackTotalTime["weak_atck1"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["weak_atck2"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["weak_atck3"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["weak_atck4"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck1"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck2"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck3"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
	_attackTotalTime["strg_atck4"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "player_lattack04")));
}


void Player::JumpAction() {

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_energy >= CHARA_DATA->_egJump) {
		if (trg & PAD_INPUT_1 && _isCanJump && !_isCharging) {
			_state = STATE::JUMP;
			_isCanJump = false;
//			_mvSpd = NOR_MV_SPD;
			_mvSpd = CHARA_DATA->_mvSpdNorm;
			_jumpTime = 0.f;
		}
	}
	if (!_isCanJump) {
		//float gravity = GRAVITY;
		float inVel = 4.0f;
		_vPos.y = inVel * _jumpTime - 0.5f * GRAVITY * _jumpTime * _jumpTime;
	}
	
	_jumpTime += 0.2f;

	if (_vPos.y < GROUND_Y) {
		_vPos.y = GROUND_Y;
		if (_isCharging == false) {
			_isCanJump = true;
		}
	}
}
/*
MATRIX Player::MV1GetFrameRotateMatrix(int MHandle, int FrameIndex, double Xaxis, double Yaxis, double Zaxis, double modelScale) {
	//親フレームの取得
	int ParentFrame = MV1GetFrameParent(MHandle, FrameIndex);

	//親フレームが存在する(=すなわちParentFrameが-2ではない)ならば相対座標分だけ平行移動する行列を取得
	//親フレームが存在しないならば単位行列を得る(=すなわち平行移動しない)   
	MATRIX MTranslate;
	if (-2 != ParentFrame)
	{
		//親子フレームの座標の取得
		VECTOR vecParent = MV1GetFramePosition(MHandle, ParentFrame);
		VECTOR vecChild = MV1GetFramePosition(MHandle, FrameIndex);

		//親を基準にした子の相対座標を取得
		VECTOR vecRerativPar2Chi = VSub(vecChild, vecParent);

		//モデルが何倍に大きくなっているかに従って相対座標を補正
		if (0 != modelScale)
		{
			modelScale = 1 / modelScale;
		}
		vecRerativPar2Chi = VScale(vecRerativPar2Chi, modelScale);
		MTranslate = MGetTranslate(vecRerativPar2Chi);
	}
	else
	{
		MTranslate = MGetIdent();
	}

	//それぞれの軸に沿って回転する行列を取得
	MATRIX MXaxis = MGetRotX(Xaxis);
	MATRIX MYaxis = MGetRotY(Yaxis);
	MATRIX MZaxis = MGetRotZ(Zaxis);

	//軸毎に回転させてから平行移動を実行する

	MATRIX MReturn = MMult(MMult(MMult(MXaxis, MYaxis), MZaxis), MTranslate);

	return MReturn;
}
*/

void Player::LeftAnalogDeg(float length){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_isCanJump) {
		if (_isDash) {
//			_mvSpd = DASH_MV_SPD;
			_mvSpd = CHARA_DATA->_mvSpdDash;
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
//			_mvSpd = NOR_MV_SPD;
			_mvSpd = CHARA_DATA->_mvSpdNorm;
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

void Player::SetAttackDamage(){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	switch (_state) {
	case STATE::WEAK_ATCK1:
		_nowDmgHP = CHARA_DATA->_wkDmgHP1;
		_nowDmgSld = CHARA_DATA->_wkDmgSld1;
		_nowDmgNorm = CHARA_DATA->_wkDmg1;
		break;
	case STATE::WEAK_ATCK2:
		_nowDmgHP = CHARA_DATA->_wkDmgHP2;
		_nowDmgSld = CHARA_DATA->_wkDmgSld2;
		_nowDmgNorm = CHARA_DATA->_wkDmg2;
		break;
	case STATE::WEAK_ATCK3:
		_nowDmgHP = CHARA_DATA->_wkDmgHP3;
		_nowDmgSld = CHARA_DATA->_wkDmgSld3;
		_nowDmgNorm = CHARA_DATA->_wkDmg3;
		break;
	case STATE::WEAK_ATCK4:
		_nowDmgHP = CHARA_DATA->_wkDmgHP4;
		_nowDmgSld = CHARA_DATA->_wkDmgSld4;
		_nowDmgNorm = CHARA_DATA->_wkDmg4;
		break;
	case STATE::STRG_ATCK1:
		_nowDmgHP = CHARA_DATA->_stDmgHP1;
		_nowDmgSld = CHARA_DATA->_stDmgSld1;
		_nowDmgNorm = CHARA_DATA->_stDmg1;
		break;
	case STATE::STRG_ATCK2:
		_nowDmgHP = CHARA_DATA->_stDmgHP2;
		_nowDmgSld = CHARA_DATA->_stDmgSld2;
		_nowDmgNorm = CHARA_DATA->_stDmg2;
		break;
	case STATE::STRG_ATCK3:
		_nowDmgHP = CHARA_DATA->_stDmgHP3;
		_nowDmgSld = CHARA_DATA->_stDmgSld3;
		_nowDmgNorm = CHARA_DATA->_stDmg3;
		break;
	case STATE::STRG_ATCK4:
		_nowDmgHP = CHARA_DATA->_stDmgHP4;
		_nowDmgSld = CHARA_DATA->_stDmgSld4;
		_nowDmgNorm = CHARA_DATA->_stDmg4;
		break;
	}
}

void Player::AttackAction() {

	int trg = ApplicationMain::GetInstance()->GetTrg();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	
	// 攻撃カウント
	if (_attackCnt <= 0) {
		_attackCnt = 0;
		_hitFlag = false;
	}
	else {
		_attackCnt--;
	}

	// 受付時間
	if (_attackCnt <= 20) {
		_receptionTime--;
	}
	if (_receptionTime <= 0) {
		_receptionTime = 0;
		_attackReloadTime = RELOAD_TIME;
		_attackFlag = false;
	}

	if (!_hitFlag) {
		if (_attackCnt >= 20 && _attackCnt < 35) {
			_canHitFlag = true;
		}
		else {
			_canHitFlag = false;
		}
	}

	switch (_state) {
	case STATE::WEAK_ATCK1:
		if (_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃2へ派生
			if (trg & PAD_INPUT_4) {                  
				if (_energy < CHARA_DATA->_egAtck2) { // エネルギー残量チェック
					return;
				}
				_state = STATE::STRG_ATCK2;
//				_status.energy -= CHARA_DATA->_egAtck2;  // エネルギー消費
				_atChargeFlag = false;                   // 攻撃中エネルギー溜め不可
				_atChargeCnt = AT_CHARGE_CNT;            // 溜め復帰時間セット
				_attackCnt = _attackTotalTime["strg_atck2"];
				_receptionTime = RECEPTION_TIME;                     // 次攻撃受付時間セット
				_hitFlag = false;
				SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット
			}
			// 弱近接攻撃2へ派生
			else if (trg & PAD_INPUT_B) {             
				_state = STATE::WEAK_ATCK2;
				_attackCnt = _attackTotalTime["weak_atck2"];
				_receptionTime = RECEPTION_TIME;                     // 次攻撃受付時間セット
				_hitFlag = false;
				SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット
			}
		}
		
		break;
	case STATE::WEAK_ATCK2:
		if (_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃3へ派生
			if (trg & PAD_INPUT_4) {                   
				if (_energy < CHARA_DATA->_egAtck3) { // エネルギー残量チェック
					return;
				}
				_state = STATE::STRG_ATCK3;
//				_status.energy -= CHARA_DATA->_egAtck3;  // エネルギー消費
				_atChargeFlag = false;                   // 攻撃中エネルギー溜め不可
				_atChargeCnt = AT_CHARGE_CNT;            // 溜め復帰時間セット
				_attackCnt = _attackTotalTime["strg_atck3"];
				_receptionTime = RECEPTION_TIME;         // 次攻撃受付時間セット
				_hitFlag = false;
				SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット
			}
			// 弱近接攻撃3へ派生
			else if (trg & PAD_INPUT_B) {              
				_state = STATE::WEAK_ATCK3;
				_attackCnt = _attackTotalTime["weak_atck3"];
				_receptionTime = RECEPTION_TIME;         // 次攻撃受付時間セット
				_hitFlag = false;
				SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット
			}
		}
		break;
	case STATE::WEAK_ATCK3:
		if (_receptionTime < RECEPTION_TIME) {
			// 強近接攻撃4へ派生
			if (trg & PAD_INPUT_4) {                   
				if (_energy < CHARA_DATA->_egAtck4) { // エネルギー残量チェック
					return;
				}
				_state = STATE::STRG_ATCK4;
//				_status.energy -= CHARA_DATA->_egAtck4;  // エネルギー消費
				_atChargeFlag = false;                   // 攻撃中エネルギー溜め不可
				_atChargeCnt = AT_CHARGE_CNT;            // 溜め復帰時間セット
			    _attackCnt = _attackTotalTime["strg_atck4"];
				_receptionTime = RECEPTION_TIME;         // 次攻撃受付時間セット
				_hitFlag = false;
				SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット
			}
			// 弱近接攻撃4へ派生
			else if (trg & PAD_INPUT_B) {              
				_state = STATE::WEAK_ATCK4;
				_attackCnt = _attackTotalTime["weak_atck4"];
				_receptionTime = RECEPTION_TIME;         // 次攻撃受付時間セット
				_hitFlag = false;
				SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット
			}
		}
		break;
		// 攻撃派生終了（弱攻撃4,強攻撃1～4）
	case STATE::WEAK_ATCK4:     
		if (_attackCnt <= 0) {
			_attackFlag = false;               // 近接攻撃終了
			_attackReloadTime = RELOAD_TIME;   // 近接攻撃リロード時間セット
		}
		break;
	case STATE::STRG_ATCK1:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // 近接攻撃終了
			_attackReloadTime = RELOAD_TIME;   // 近接攻撃リロード時間セット
		}
		break;
	case STATE::STRG_ATCK2:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // 近接攻撃終了
			_attackReloadTime = RELOAD_TIME;   // 近接攻撃リロード時間セット
		}
		break;
	case STATE::STRG_ATCK3:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // 近接攻撃終了
			_attackReloadTime = RELOAD_TIME;   // 近接攻撃リロード時間セット
		}
		break;
	case STATE::STRG_ATCK4:
		if (_attackCnt <= 0) {
			_attackFlag = false;               // 近接攻撃終了
			_attackReloadTime = RELOAD_TIME;   // 近接攻撃リロード時間セット
		}
		break;
	}
}


void Player::EnergyManager(STATE oldState){

	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float addEne;

	if (_energy > CHARA_DATA->_maxEnergy) {  // エネルギー回復時に最大エネルギー値を超えるのを防ぐ
		_energy = CHARA_DATA->_maxEnergy;

	}

	if (oldState != _state) { 
		// ジャンプ(消費)
		if (_state == STATE::JUMP) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
//			_energy -= JUMP_ENERGY;
			_energy -= CHARA_DATA->_egJump;
		}
		// 短押しダッシュ(消費)
		if (_isShortDash) {
			_atChargeFlag = false;
			_atChargeCnt = AT_CHARGE_CNT;
//			_energy -=  DASH_ENERGY;
			_energy -= CHARA_DATA->_egDash;
		}
	}

	// 長押しダッシュ(消費)
	if(!_isShortDash && _isDash) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
		_energy--;
	}

	// マルチロックオンシステム(消費)
	if (camState == Camera::STATE::MLS_LOCK) {
		_atChargeFlag = false;
		_atChargeCnt = AT_CHARGE_CNT;
//		_energy -= 12.5;
		_energy -= CHARA_DATA->_egMLS;
	}

	// ボス付近で行動する(回復)
	if (_nearPosFlag) {
		addEne = CHARA_DATA->_egAutoXArea;
	}
	else {
		addEne = 1.0f;
	}

	if (_energy >= CHARA_DATA->_maxEnergy) {
		return;
	}
	//　溜め(回復)
	if (_isCharging) {
//		_atChargeCnt = AT_CHARGE_CNT;
//		_energy += AT_CHARGE * 2.5 * addEne;
		_energy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
		gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * CHARA_DATA->_egAutoXChrg * addEne;
	}

	// 自動回復開始のインターバル
	if (!_atChargeFlag) {
		_atChargeCnt--;
		if (_atChargeCnt <= 0){   // 一定の自動回復開始間隔を設ける
			_atChargeCnt = 0;
			_atChargeFlag = true;
		}
	}
	// 自動回復(回復)
	else if (!_isCharging){
//		_status.energy += AT_CHARGE * addEne;
		_energy += CHARA_DATA->_egAutoRec * addEne;
		gGlobal._totalGetEnergy += CHARA_DATA->_egAutoRec * addEne;
	}
}

void Player::Process(){

	// キーの取得
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// 当たり判定用カプセル情報
	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

	// アナログスティック対応
	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	float lx, ly;           // 左アナログスティックの座標
	int rt = dinput.Z;    // ゲームパッド「RT」
	float analogMin = 0.3f;
	lx = static_cast<float>(dinput.X);
	ly = static_cast<float>(dinput.Y);

	// 処理前のステータスを保存
	STATE oldState = _state;

	// 処理前の位置を保存
	_oldPos = _vPos;

	// ボスデータ取得
	{
		VECTOR bsPos = Boss::GetInstance()->GetPos();
		float dx = _vPos.x - bsPos.x;
		float dz = _vPos.z - bsPos.z;
		float len = sqrt(dx * dx + dz * dz);
		_len = len;            //デバッグ用
		_bsAngle = atan2(dz, dx);
		if (len <= 50) {
			_nearPosFlag = true;
		}
		else {
			_nearPosFlag = false;
		}
	}

	// カメラデータ取得
	VECTOR camPos = Camera::GetInstance()->GetPos();
	VECTOR camTarg = Camera::GetInstance()->GetTarg();
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// カメラの向いている角度取得
	float disX = camPos.x - camTarg.x;
	float disZ = camPos.z - camTarg.z;
	float camRad = atan2(disZ, disX);

	// モードゲーム取得
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));


	// 移動方向を決める
	VECTOR vec = { 0.f,0.f,0.f };
	float length = sqrt(lx * lx + ly * ly);
	float rad = atan2(lx, ly);
	_lfAnalogDeg = static_cast<int>(rad * 180.0f / DX_PI_F);


	/**
	* ゲームオーバー処理
	*/
	if (_gameOverFlag) {
		_gameOverCnt--;
		if (_gameOverCnt == 0) {
			ModeGameOver* modeGameOver = new ModeGameOver();
			ModeServer::GetInstance()->Add(modeGameOver, 2, "over");
		}
	}
	if (_hitpoint <= 0) {   // ヒットポイント 0 でゲームオーバー
		_gameOverFlag = true;
	}


	/**
	* 移動処理
	*/
	if (length < analogMin) {
		length = 0.f;
	}
	else {
		length = _mvSpd;
	}

	if (camState != Camera::STATE::MLS_LOCK && !_attackFlag) {  // マルチロックシステムが発動していないときは移動可能
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
//					_mvSpd = NOR_MV_SPD;
					_mvSpd = CHARA_DATA->_mvSpdNorm;
				}				
			}
			else {
				_vDir = vec;
				if (_state != STATE::FOR_DASH) {
//					_mvSpd = NOR_MV_SPD;
					_mvSpd = CHARA_DATA->_mvSpdNorm;
				}
				if (_isCanJump) {
					_state = STATE::WALK;
				}
			}
		}
		else if (_isCanJump && !_shotFlag && !_attackFlag) {
			_state = STATE::WAIT;

		}

		/**
        * 重力処理
        */
		_vPos.y -= GRAVITY;
		if (_vPos.y < 0.0f) {
			_vPos.y = 0.0f;
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
		if (trg & PAD_INPUT_6 && (_state != STATE::JUMP) && _energy > CHARA_DATA->_egDash) {
			_mvSpd = CHARA_DATA->_mvSpdDash;
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
			if (_isCanJump && _isCanLongDash && !_isShortDash && _energy > 0) {
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
		* エネルギー溜め
		*/
		if (key & PAD_INPUT_3 && !(key & PAD_INPUT_5)&& _energy < CHARA_DATA->_maxEnergy) {
			if (_state != STATE::JUMP) {  // ジャンプしてなければ溜め可能
				if (!_isDash) {           // ダッシュしてなければ溜め可能
//					_mvSpd = CHARGE_MV_SPD;
					_mvSpd = CHARA_DATA->_mvSpdChrg;
					_isCharging = true;
				}
			}
		}
		else {
			_isCharging = false;
		}

		/**
		* 近接攻撃処理(初手のみ)
		*/
		if (_vPos.y == 0.0f && _attackReloadTime == 0) {
			if (trg & PAD_INPUT_B && !_attackFlag) {
				_state = STATE::WEAK_ATCK1;
				_attackFlag = true;
				_attackCnt = _attackTotalTime["weak_atck1"];
				_receptionTime = RECEPTION_TIME;
				_hitFlag = false;
				SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット

			}
			if (trg & PAD_INPUT_4 && !_attackFlag) {
				if (_energy >= CHARA_DATA->_egAtck1) {  // エネルギー残量チェック
					_state = STATE::STRG_ATCK1;
					_energy -= CHARA_DATA->_egAtck1;    // エネルギー消費
					_atChargeFlag = false;                     // 攻撃中エネルギー溜め不可 
					_atChargeCnt = AT_CHARGE_CNT;              // 溜め復帰時間セット
					_attackFlag = true;
					_attackCnt = _attackTotalTime["strg_atck1"];
					_receptionTime = RECEPTION_TIME;
					_hitFlag = false;
					SetAttackDamage();   // 現在の近接攻撃のボスへのダメージ量をセット
				}
			}
		}
		

		/**
		* 射撃攻撃 (ゲームパッドRTで射撃)
		*/
		int rtMin = -100;
		if (rt < rtMin && !_isCharging && !_shotZeroFlag) { // 溜め状態及び装弾数がゼロになった場合は射撃不可
			if (_bulletNum == 0) {
				_shotZeroFlag = true;      // 弾を打ち切ってしまうとフラグが立つ(= true) ⇒ 射撃不可
			}
			if (_bulletNum > 0) {
				if (_canShotFlag) {
					_state = STATE::SHOT_ATCK;
					_shotFlag = true;
					_playTime = 30.0f;
					_reloadTime = RELOAD_TIME;	   // リロード開始時間をセット
					_canShotFlag = false;
					_bulletNum--;
//					ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
					PlayerBullet* bullet = new PlayerBullet();
					float angle = atan2(_vDir.z, _vDir.x);
					VECTOR tmp = _vPos;
					tmp.y = _vPos.y + 5.5f;
					bullet->SetPos(tmp);
					bullet->SetShotAngle(angle);
					modeGame->_objServer.Add(bullet);  // 弾発生、射撃開始
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
			_shotFlag = false;
			_reloadTime--;
			if (_shotZeroFlag) {            // 弾を打ち切った場合は即時リロード開始
				if (_bulletNum < MAX_BULLET) {
					_bulletNum++;
				}
			}
			else if (_reloadTime <= 0) {    // 弾が残っている状態かつリロード開始時間ゼロでリロード開始
				if (_bulletNum < MAX_BULLET) {
					_bulletNum++;
				}
			}

		}
		if (_bulletNum == MAX_BULLET) {
			_shotZeroFlag = false;          // リロード完了で_shotZeroFlag解除(= false)
		}
	}

	/**
    * 近接攻撃処理(2発目以降)
    */
	if (_attackFlag) {
		AttackAction();
	}
	if (_attackReloadTime > 0) {
		_attackReloadTime--;
	}

	if (_camStateMLS) {
		_vDir.x = -cos(_bsAngle);
		_vDir.z = -sin(_bsAngle);
		_state = STATE::NONE;
	}
		

	/**
	*  マルチロックシステム用レチクル追加
	*/
	if (trg & PAD_INPUT_5) {
		_camStateMLS = true;
//		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		Reticle* reticle = new Reticle();
		modeGame->_objServer.Add(reticle);
	}
	else {
		_camStateMLS = false;
	}



	/**
	* エネルギー管理
	*/
	if (_energy > 0 || _energy < CHARA_DATA->_maxEnergy) {
		if (_swCharge) {               // デバッグ用
			EnergyManager(oldState);
		}
	}
	if (_energy < 0) {
		_energy = 0;
	}
	if (_energy > CHARA_DATA->_maxEnergy) {
		_energy = CHARA_DATA->_maxEnergy;
	}

	// デバッグ用
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
//		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::STAGE) {  // ステージ
				if (IsHitStage(*(*itr), 2.0f) == true) {
					VECTOR slideVec;
					slideVec = VCross(_vDir, (*itr)->_hitPolyDim.Dim->Normal);
					slideVec = VCross((*itr)->_hitPolyDim.Dim->Normal, slideVec);
					_vPos = VAdd(_oldPos, slideVec);
					_vPos = VAdd(_vPos, VScale((*itr)->_hitPolyDim.Dim->Normal, 0.5f));
					//					_vPos = VAdd(_vPos, (*itr)->_hitPolyDim.Dim->Normal);
				}
				

			}
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) { // ボスの弾
				// 着弾
				if (IsHitLineSegment(*(*itr), 1.5f)) {
					modeGame->_objServer.Del(*itr);
					_hitpoint -= CHARA_DATA->_boss.shotDmg;
				}
				// カスリ判定(エネルギー回復)
				if (IsHitLineSegment(*(*itr), 2.5f)) {
//					_status.energy += 3;
					_energy += CHARA_DATA->_egAvoid;
					gGlobal._totalGetEnergy += CHARA_DATA->_egAvoid;
				}
				if (Boss::GetInstance()->_mlsDownFlag) {
					modeGame->_objServer.Del(*itr);
					
				}
			}
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS) { // ボス
				if (IsHitArc_Sphere(*(*itr))==true) {
					if (_canHitFlag && !_hitFlag) {
						_hitFlag = true;
						(*itr)->AttackDamage();
					}
				}
				if (IsHitLineSegment(*(*itr), 10.0f)) {
				
					
					_vPos = VAdd(_vPos, VScale(_oldPos, 0.4f));

				}
			}
		}
	}
	// MLSによる弾き返しでシールド破壊した場合、[ボスの弾の数 * 指定のエネルギー量]分回復する。
	if (Boss::GetInstance()->_mlsDownFlag) {
		_energy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
		gGlobal._totalGetEnergy += (CHARA_DATA->_egShotNum * Boss::GetInstance()->_bulletNum);
	}

	/**
	* モーション切替
	*/
	if (oldState == _state) {
		_playTime += 1.0f;
	}
	else {
		if (_attachIndex != -1) {
			MV1DetachAnim(_mh, _attachIndex);
			_attachIndex = -1;
//			MV1ResetFrameUserLocalMatrix(_mh, 94);
		}
		switch (_state) {
		case STATE::WAIT:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "waitmove"), -1, FALSE);
			break;
		case STATE::WALK:
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "run"), -1, FALSE);
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
		case STATE::WEAK_ATCK1:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);

			break;
		case STATE::WEAK_ATCK2:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::WEAK_ATCK3:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::WEAK_ATCK4:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK1:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK2:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK3:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::STRG_ATCK4:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "player_lattack04"), -1, FALSE);
			break;
		case STATE::SHOT_ATCK:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "shoot"), -1, FALSE);
//			MATRIX Mrotate = MV1GetFrameRotateMatrix(_mh, 94, 0, 0.2 * 2 * DX_PI_F, 0, 0.1);
//			MV1SetFrameUserLocalMatrix(_mh, 94, Mrotate);
			break;
		}

		// アタッチしたアニメーションの総再生時間を取得する
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}

	if (!_attackFlag) {
		if (_playTime >= _totalTime) {
			_playTime = 0.0f;
		}
	}

	// 残りHP保存(スコア計算用)
	gGlobal._remainingHP = _hitpoint;
}

void Player::Render(){
    MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(0.1f, 0.1f, 0.1f));
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
	float angle = atan2(_vDir.z ,_vDir.x);
	float deg = angle * 180.f / DX_PI_F;
	int x = 100;
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
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP     = %d", _hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  energy = %d, ON(1) / OFF(0) = %d (BACKキーで切替)", _energy, _swCharge); y += size;

	DrawFormatString(0, y, GetColor(255, 0, 0), "  ボスとの距離 = %4.2f", _len); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  攻撃カウント = %d", _attackCnt); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  攻撃受付時間 = %d", _receptionTime); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  攻撃ﾘﾛｰﾄﾞ時間 = %d", _attackReloadTime); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ダメージHP = %d", _nowDmgHP); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ダメージSLD= %d", _nowDmgSld); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ダメージ通常 = %d", _nowDmgNorm); y += size;
	DrawString(0, y, "　状態：",GetColor(255, 0, 0));
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
	case STATE::SHOT_ATCK:
		DrawString(x, y, "SHOT ATTACK", GetColor(255, 0, 0)); break;
	}

	DrawFormatString(0, 900, GetColor(255, 0, 0), "  装弾数 = %d / 100", _bulletNum); 
//	DrawCapsule3D(_capsulePos1, _capsulePos2, 1.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
//	DrawCapsule3D(_capsulePos1, _capsulePos2, 2.5f, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);
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