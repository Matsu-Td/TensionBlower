/**
 * @file   Boss.cpp
 * @brief  ボスクラス
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
 * 声データ再生
 */
void Boss::PlayVoice(std::string voiceName) {
	PlaySoundMem(gBossVoice._vc[voiceName], DX_PLAYTYPE_BACK);
}

/**
 * 6種類の声データをランダムで流す
 */
void Boss::PlayAttackVoiceChange() {

	int voiceNo = rand() % ATTACK_VOICE_NUM;
	PlayVoice(_attackNameNo[voiceNo]);
}

/**
 * フェーズ変更処理
 */
void Boss::FhaseChange() {

	// フェーズ4へ移行
	if (_hitpoint <= PHASE_FOUR_HP) {
		_phase = 4;
		return;
	}
	// フェーズ3へ移行
	if (_hitpoint <= PHASE_THREE_HP) {
		_phase = 3;
		return;
	}
	// フェーズ2へ移行
	if (_hitpoint <= PHASE_TWO_HP) {
		_phase = 2;
		return;
	}
	// フェーズ1へ移行
	if (_hitpoint <= PHASE_ONE_HP) {
		_phase = 1;
		return;
	}
	// 初期フェーズ0
	_phase = 0;
}

/**
 * ダウン状態処理
 */
void Boss::StateDown(){

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// 復帰
	if (_state == STATE::DOWN) {
		_vPos.y = 0.0f;
		_mlsDownFlag = false;	   // マルチロックオンシステムによるダウンフラグ解除
		_downTime--;               // ダウン時間カウント
		if (_downTime < 0) {
			// 復帰時の声データ再生
			PlayVoice("hukki");
			_downTime = 0;         // ダウン時間リセット
			_state = STATE::RETURN;// 復帰状態にさせる
			_bulletNum = 0;        // 弾の数リセット
			_shield = modeGame->_charaData->_boss.maxShield;  // シールド値全回復
		}
	}

	if (_shield > 0) {
		return;
	}
	// ダウン
	if (_state == STATE::NORMAL) {
		PlaySoundMem(gSound._se["down"], DX_PLAYTYPE_BACK);
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
				_bulletNum++;   // ダウン直前に出現していた弾の数をカウント
			}
			int plEnergy = Player::GetInstance()->GetEnergy();            // プレイヤーのエネルギー情報取得
			_downTime = MIN_DOWN_TIME + plEnergy / 20 + _bulletNum;       // ダウン時間計算                                           // ダウン状態にする
			_state = STATE::DOWN;
		}
	}
}

/**
 * ゲームクリア処理
 */
void Boss::Dead() {

	// ゲームクリア処理スタート
	if (_deadFlag) {
		_deadCnt--;
		if (_deadCnt == 0) {
			MV1DeleteModel(_mh); // ボスモデルを削除する
		}
	}
	// ヒットポイントゼロでゲームクリアフラグを立てる
	if (_hitpoint <= 0) {
		if (!_deadFlag) {
			// 撃破時の声データ再生
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
 * モーション切替
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
			_attachIndex = -1; // 通常はモーション無し
			break;
		case STATE::DOWN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "down"), -1, FALSE);
			break;
		case STATE::RETURN:
			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "return"), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

		_playTime = 0.0f;
	}
}

/**
 * ボス正面方向回転処理
 */
void Boss::DirectionalRotation(float rotSpdChenge) {

	// プレイヤーの位置情報取得
	VECTOR plPos = Player::GetInstance()->GetPos();

	// ボスのフォワードベクトル
	VECTOR forward = { cos(_angle),0.0f,sin(_angle) };

	// プレイヤーに向かうベクトル
	VECTOR dis = VSub(plPos, _vPos);
	// 単位ベクトル化
	dis = VNorm(dis);

	// 外積でプレイヤーの位置を左右判定し、ボスの向きを回転させる
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
 * フレーム処理：計算
 */
void Boss::Process(){

	// カメラの状態を取得
	Camera::STATE camState = Camera::GetInstance()->GetCameraState();
	
	STATE oldState = _state;

	// 死亡処理
	Dead();

	if (_deadFlag) {
		return;
	}
	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos1.y = _vPos.y + ADD_POS_Y;   // y座標(高さ)のみ加算
	_capsulePos2 = _vPos;
	_capsulePos2.y = _vPos.y + ADD_POS_Y;   // y座標(高さ)のみ加算

	// 復帰状態
	if (_state == STATE::RETURN) {
		if (_playTime == _totalTime) {
			_state = STATE::NORMAL;
		}
	}

	// 通常状態
	if (_state == STATE::NORMAL) {
		// ボスの回転速度切替用
		float rotSpdChenge = 1.0f;

		// 弾幕攻撃処理
		if (_shield > 0) {
			// マルチロックオンシステム発動中は弾の発射速度を遅くする
			if (camState == Camera::STATE::MLS_LOCK) {
				_mlsCnt++;
				rotSpdChenge = 0.01f;
				if (_mlsCnt % 100 == 0) {
					_patternCall->ShotPatternSwitch(this);
				}
			}
			// 通常時
			else {
				_mlsCnt = 0;
				_patternCall->ShotPatternSwitch(this);
			}
		}
		// ボスの上下運動
		_sinCnt += 1.0f * rotSpdChenge;
		_vPos.y = 2.0f - sin(DX_PI_F / 90.0f * _sinCnt) * 2.0f;

		// プレイヤーがいる方向にボスの正面を向ける
		DirectionalRotation(rotSpdChenge);
		
	}

	// フェーズ切替
	FhaseChange();
	
	// ダウン処理
	StateDown();

	// モーション切替
	MotionSwitch(oldState);
}

/**
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
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Boss:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos     = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  dir     = (%5.2f, %5.2f, %5.2f)", _vDir.x, _vDir.y, _vDir.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  cross     = (%5.2f, %5.2f, %5.2f)", _cross.x, _cross.y, _cross.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP　    = %d", _hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ｼｰﾙﾄﾞ値 = %d", _shield);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  出現している弾の数 = %d", _bulletNum);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ダウン時間 = %d", _downTime);   y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  _vDir.y = %f", _vDir.y); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  状態 = %d", _state); y += size;
	DrawCapsule3D(_capsulePos1, _capsulePos2, 10.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}