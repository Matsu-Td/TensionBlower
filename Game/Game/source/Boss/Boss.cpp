/**
 * @file   Boss.cpp
 * @brief  ボスクラス
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
 * 初期化
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

	_patternRandom = 1;
	_shotAngle = -90.0f;
	_shotAngleUp = -90.0f;
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
	_phaseNo = 0;

	_deathCnt = 140;
	_deathFlag = false;

	_r = 10.0f;
}

/*
 * フレーム処理：計算
 */
void Boss::Process(){

	// カメラの状態を取得
	Camera::STATE camState = Camera::GetInstance()->GetState();
	
	// 処理前の状態を保存
	_oldState = _state;

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos1.y = _vPos.y + ADD_POS_Y;   // y座標(高さ)のみ加算
	_capsulePos2 = _vPos;
	_capsulePos2.y = _vPos.y + ADD_POS_Y;   // y座標(高さ)のみ加算

    // 死亡処理
	Death();

	// 死亡したら以降の処理は行わない
	if (_deathFlag) {
		return;
	}

	// 復帰
	if (_state == STATE::RETURN) {
		if (_playTime == _totalTime) {
			_state = STATE::NORMAL;
		}
	}

	// 通常状態
	if (_state == STATE::NORMAL) {
		// ボスの回転速度切替用
		float rotSpdChange = 1.0f;

		// 弾幕攻撃処理
		if (_shield > 0) {
			// マルチロックオンシステム発動中は行動と弾の発射速度を遅くする
			if (camState == Camera::STATE::MLS_LOCK) {
				_mlsCnt++;
				rotSpdChange = 0.01f;
				if (_mlsCnt % 100 == 0) {
					BarragePatternSwitch();
				}
			}
			// 通常時
			else {
				_mlsCnt = 0;
				BarragePatternSwitch();
			}
		}
		// ボスの上下運動
		_sinCnt += 1.0f * rotSpdChange;
		_vPos.y = 2.0f - sin(DX_PI_F / 90.0f * _sinCnt) * 2.0f;

		// プレイヤーがいる方向にボスの正面を向ける
		DirectionalRotation(rotSpdChange);
		
	}

	// フェーズ切替
	FhaseChange();
	
	// ダウン処理
	StateDown();

	// モーション切替
	MotionSwitch();
}

/*
 * フレーム処理：描画
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
	int fontSize = 24;
	int fontColor = GetColor(255, 0, 0);
	SetFontSize(fontSize);
	DrawFormatString(0, y, fontColor, "Boss:"); y += fontSize;
	DrawFormatString(0, y, fontColor, "  pos     = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += fontSize;
	DrawFormatString(0, y, fontColor, "  dir     = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += fontSize;
	DrawFormatString(0, y, fontColor, "  cross     = (%5.2f, %5.2f, %5.2f)", _cross.x, _cross.y, _cross.z); y += fontSize;
	DrawFormatString(0, y, fontColor, "  HP　    = %d", _hitpoint); y += fontSize;
	DrawFormatString(0, y, fontColor, "  ｼｰﾙﾄﾞ値 = %d", _shield);  y += fontSize;
	DrawFormatString(0, y, fontColor, "  出現している弾の数 = %d", _bulletNum);  y += fontSize;
	DrawFormatString(0, y, fontColor, "  ダウン時間 = %d", _downTime);   y += fontSize;
	DrawFormatString(0, y, fontColor, "  _vDir.y = %f", _vDir.y); y += fontSize;
	DrawFormatString(0, y, fontColor, "  状態 = %d", _state); y += fontSize;
	DrawCapsule3D(_capsulePos1, _capsulePos2, 10.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}