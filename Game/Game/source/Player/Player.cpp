/**
 * @file   Player.cpp
 * @brief  プレイヤークラス
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "Player.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeGame.h"

Player* Player::_pInstance = nullptr;

Player::Player(){

	_pInstance = this;

	_mh = MV1LoadModel("res/model/player/pl_model_mm.mv1");
	_shadowModel = MV1LoadModel("res/model/player/pl_model_mm_shadow.mv1");
//	MV1SetAttachAnimTime(_shadowModel, MV1AttachAnim(_shadowModel, 0, -1, FALSE), 0.0f);
	
	Initialize();
}

Player::~Player(){
	MV1DeleteModel(_mh);
	MV1DeleteModel(_shadowModel);
}

/*
 * 初期化
 */
void Player::Initialize(){
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	_vPos = VGet(0.0f, 0.0f, -115.0f);
	_vDir = VGet(0, 0, 1);
	_mvSpd = modeGame->_charaData->_mvSpdNorm;
	_attachIndex = -1;
	_attachIndexShadow = -1;
	_totalTime = 0;
	_playTime = 0.0f;

	// ヒットポイント
	_hitpoint = modeGame->_charaData->_maxHP;

	// ジャンプ
	_jumpTime = 0.0f;
	_canJump = true;

	// ダッシュ
	_isDash = false;
	_isShortDash = false;
	_canLongDash = false;

	// エネルギー
	_energy = modeGame->_charaData->_maxEnergy;
	_isCharging = false;
	_canAutoCharge = true;
	_autoChargeCnt = 30;

	// 近接攻撃
	_isAttack = false;
	_attackCnt = 0;
	_attackReloadTime = 0;
	_receptionTime = 0;
	_hitFlag = false;
	_canHitFlag = false;

	// ゲームオーバー
	_gameOverCnt = 160;
	_isGameOver = false;

	// 各近接攻撃のアニメーション総再生時間を格納
	_mapAttackTotalTime["slash_l"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "slash_l")));
	_mapAttackTotalTime["slash_h"] = static_cast<int>(MV1GetAnimTotalTime(_mh, MV1GetAnimIndex(_mh, "slash_h")));
}

/*
 * 重力処理
 */
void Player::Gravity() {
	_vPos.y -= GRAVITY;
	if (_vPos.y < 0.0f) {
		_vPos.y = 0.0f;
	}
}

/*
 * フレーム処理：計算
 */
void Player::Process(){

	// 当たり判定用カプセル情報
	_capsulePos1 = VGet(_vPos.x, _vPos.y + 2.1f, _vPos.z);
	_capsulePos2 = VGet(_vPos.x, _vPos.y + 7.0f, _vPos.z);

	// 処理前のステータスを保存
	_oldState = _state;

	// 処理前の位置を保存
	_oldPos = _vPos;

	// 死亡処理＆ゲームオーバーへ移行
	Death();

	// カメラ状態取得
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();

	// マルチロックシステムが発動していない
	// 近接攻撃を発動していない
	// ゲームオーバーになっていない
	if (camState != Camera::STATE::MLS_LOCK && !_isAttack && !_isGameOver) {
		
		// 移動処理
		Move();

		// 重力処理
		Gravity();

		// ジャンプ
		Jump();
		
		// ダッシュ処理
		Dash();

		// 溜めチャージ処理
		Charge();

		// 近接攻撃(初手のみ)
		if (_vPos.y == 0.0f) {
			FirstAttack();
		}
	}

    // 近接攻撃処理(2発目以降)
	SecondAttack();

	// マルチロックオンシステム用照準追加
	ReticleGeneration();

	// エネルギー管理
	EnergyManager();

	// 当たり判定
	AllCollision();

	// モデルモーション切替
	MotionSwitching();

	// HP下限値保持
	if (_hitpoint <= 0) {
		_hitpoint = 0;
	}

	// 残りHP保存(スコア計算用)
	gGlobal._remainingHP = _hitpoint;
}

/*
 * フレーム処理：描画
 */
void Player::Render(){

	ObjectBase::ShadowRender();

    MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetAttachAnimTime(_shadowModel, _attachIndexShadow, _playTime);
	{
		MV1SetPosition(_mh, _vPos);
		// 向きからY軸回転を算出
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);
		MV1SetRotationXYZ(_mh, vRot);
		MV1DrawModel(_mh);
	}

#ifdef _DEBUG
	float rad = atan2(_vDir.z ,_vDir.x);
	float deg = Util::RadToDeg(rad);
	int x = 100;
	int y = 340;
	int fontSize = 24;
	int fontColor = GetColor(255, 0, 0);
	SetFontSize(fontSize);
	DrawFormatString(0, y, fontColor, "Player:"); y += fontSize;
	DrawFormatString(0, y, fontColor, "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += fontSize;
	DrawFormatString(0, y, fontColor, "  dir    = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += fontSize;
	DrawFormatString(0, y, fontColor, "  deg    = %5.1f", deg); y += fontSize;
	DrawFormatString(0, y, fontColor, "  spd    = %3.1f", _mvSpd); y += fontSize;
	DrawFormatString(0, y, fontColor, "  charge = %d", _isCharging); y += fontSize;
	DrawFormatString(0, y, fontColor, "  dash   = %d", _isDash); y += fontSize;
	DrawFormatString(0, y, fontColor, "  左ST角度 = %d", _lfAnalogDeg); y += fontSize;
	DrawFormatString(0, y, fontColor, "  HP     = %d", _hitpoint); y += fontSize;

	DrawFormatString(0, y, fontColor, "  攻撃カウント = %d", _attackCnt); y += fontSize;
	DrawFormatString(0, y, fontColor, "  攻撃受付時間 = %d", _receptionTime); y += fontSize;
	DrawFormatString(0, y, fontColor, "  攻撃ﾘﾛｰﾄﾞ時間 = %d", _attackReloadTime); y += fontSize;
	DrawFormatString(0, y, fontColor, "  ダメージHP = %d", _nowDmgHP); y += fontSize;
	DrawFormatString(0, y, fontColor, "  ダメージSLD= %d", _nowDmgSld); y += fontSize;
	DrawFormatString(0, y, fontColor, "  ダメージ通常 = %d", _nowDmgNorm); y += fontSize;
	DrawString(0, y, "　状態：", fontColor);
	switch (_state) {
	case STATE::WAIT:
		DrawString(x, y, "WAIT", fontColor); break;
	case STATE::WALK:
		DrawString(x, y, "WALK", fontColor); break;
	case STATE::FOR_DASH:
		DrawString(x, y, "FOR DASH", fontColor); break;
	case STATE::JUMP:
		DrawString(x, y, "JUMP", fontColor); break;
	case STATE::LEFT_MOVE:
		DrawString(x, y, "LEFT MOVE", fontColor); break;
	case STATE::RIGHT_MOVE:
		DrawString(x, y, "RIGHT MOVE", fontColor); break;
	case STATE::BACK_MOVE:
		DrawString(x, y, "BACK MOVE", fontColor); break;
	case STATE::LEFT_DASH:
		DrawString(x, y, "LEFT DASH", fontColor); break;
	case STATE::RIGHT_DASH:
		DrawString(x, y, "RIGHT DASH", fontColor); break;
	case STATE::BACK_DASH:
		DrawString(x, y, "BACK DASH", fontColor); break;
	case STATE::WEAK_ATCK1:
		DrawString(x, y, "WEAK ATTACK1", fontColor); break;
	case STATE::WEAK_ATCK2:
		DrawString(x, y, "WEAK ATTACK2", fontColor); break;
	case STATE::WEAK_ATCK3:
		DrawString(x, y, "WEAK ATTACK3", fontColor); break;
	case STATE::WEAK_ATCK4:
		DrawString(x, y, "WEAK ATTACK4", fontColor); break;
	case STATE::STRG_ATCK1:
		DrawString(x, y, "STRG ATTACK1", fontColor); break;
	case STATE::STRG_ATCK2:
		DrawString(x, y, "STRG ATTACK2", fontColor); break;
	case STATE::STRG_ATCK3:
		DrawString(x, y, "STRG ATTACK3", fontColor); break;
	case STATE::STRG_ATCK4:
		DrawString(x, y, "STRG ATTACK4", fontColor); break;
	}

#endif
}

void Player::ExplosionDamage(){
	
	if (_hitpoint > 0) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		_hitpoint -= modeGame->_charaData->_boss.explosionDmg;
	}
}
