/**
 * @file   Boss.cpp
 * @brief  ボス関連処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "Boss.h"
#include "ModeGame.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "ModeGameClear.h"
#include "BossBullet.h"
#include "BossBomb.h"
#include "Sound.h"


Boss* Boss::_pInstance = NULL;

Boss::Boss(){

	_pInstance = this;
	_mh = MV1LoadModel("res/model/boss/Tboss_model_mm.mv1");

	Initialize();
}

Boss::~Boss(){

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

	_attachIndex = -1;
	_totalTime = 0.0f;
	_playTime = 0.0f;

	_shotPattern = 1;
	_shotAngle = -90.0f;
	_shotAngle1 = -90.0f;
	_shotCnt = 0;
	_mlsCnt = 0;
	_reverseCnt = 60;
	_setRotAngle = 1.0f;
	_shotHeight = 0.0f;

	_hitpoint = CHARA_DATA->_boss.maxHP;
	_shield = CHARA_DATA->_boss.maxShield;
	_bulletNum = 0;
	_stateDown = false;
	_mlsDownFlag = false;
	_downTime = 0;
	_phase = 0;

	_gameClearCnt = 60;
	_gameClearFlag = false;
}

/**
 * 弾幕パターン切替処理
 */
void Boss::ShotPatternSwitch() {

	_shotCnt++;

	// フェーズ毎で発生する弾幕パターンを3セットランダムで変化させる
	if (_shotCnt % PATTERN_CHANGE_CNT == 0) {
		_shotPattern = rand() % 3 + 1;
	}

	// フェーズ毎の弾幕パターンセット
	switch (_phase) {
	// 初期フェーズ
	case 0:                      
		if(_shotPattern <= 2){
			ShotPattern1and2();
		}
		else {
			ShotPattern3();
		}
		break;
	// フェーズ1
	case 1:	                     
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern6();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
		}
		if (_shotPattern == 3) {
     		ShotPattern5();
		}
		break;
	// フェーズ2
	case 2:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern7();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			ShotPattern6();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			ShotPattern6();
		}
		break;
	// フェーズ3
	case 3:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern6();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			ShotPattern6();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			ShotPattern6();
		}
		break;
	// フェーズ4
	case 4:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern7();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			ShotPattern6();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			ShotPattern6();
		}
		break;
	}
}

/**
 * 弾幕パターン1&2
 */
void Boss::ShotPattern1and2() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_shotCnt % 17 == 0 && _shotCnt != 1) {  
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			BossBullet* bullet = NEW BossBullet();
			bullet->SetPos(tmpPos);           // 弾幕発生位置セット
			bullet->SetShotSpd(1.0f);         // 弾の移動速度セット
			bullet->SetAngle(_shotAngle);     // 弾の発射角度セット
			modeGame->_objServer.Add(bullet); // 弾生成
			_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}
	}
	else {
		if (_shotPattern == 1) {
			_shotAngle += 2.0f;   // 毎フレーム発射角度を2°ずらす
		}
		else if (_shotPattern == 2) {
			_shotAngle -= 2.0f;   // 毎フレーム発射角度を2°ずらす
		}
	}
}

/**
 * 弾幕パターン3
 */
void Boss::ShotPattern3() {

	_reverseCnt--;
	if (_reverseCnt <= 0) {
		_reverseCnt = SHOT_REVERSE_CNT;
		_setRotAngle *= -1.0f;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_shotCnt % 9 == 0) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 4.5f;
			tmpPos.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet();
			bullet->SetPos(tmpPos);           // 弾幕発生位置セット
			bullet->SetShotSpd(1.3f);         // 弾の移動速度セット
			bullet->SetAngle(_shotAngle);     // 弾の発射角度セット
			modeGame->_objServer.Add(bullet); // 弾生成
			_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}
		
	}
	else {
		_shotAngle += _setRotAngle;
	}
}

/**
 * 弾幕パターン4-1
 */
void Boss::ShotPattern4_1() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 26 == 0) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 3.5f;
			tmpPos.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet();
			bullet->SetPos(tmpPos);           // 弾幕発生位置セット
			bullet->SetShotSpd(1.2f);         // 弾の移動速度セット
			bullet->SetAngle(_shotAngle);     // 弾の発射角度セット
			modeGame->_objServer.Add(bullet); // 弾生成
			_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}
	}
	else {
		_shotAngle += 2.0f;    // 毎フレーム発射角度を2°ずらす
	}
}

/**
 * 弾幕パターン4-2
 */
void Boss::ShotPattern4_2() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 26 == 13) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = _vPos.x + cos(_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 5.0f;
			tmpPos.z = _vPos.z + sin(_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet();
			bullet->SetPos(tmpPos);           // 弾幕発生位置セット
			bullet->SetShotSpd(1.2f);         // 弾の移動速度セット
			bullet->SetAngle(_shotAngle1);    // 弾発射角度セット
			modeGame->_objServer.Add(bullet); // 弾生成
			_shotAngle1 += 45.0f;             // 弾発射角度を45°ずつずらす
		}
	}
	else {
		_shotAngle1 -= 2.0f;    // 毎フレーム発射角度を2°ずらす
	}
}

/**
 * 弾幕パターン5
 */
void Boss::ShotPattern5() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// プレイヤー位置取得
	VECTOR plPos = Player::GetInstance()->GetPos();

	// 同時に7発弾を発射する
	if (_shotCnt % 8 == 0) {
		float angleSide = -30.0f;
		float height = _shotHeight;
		for (int i = 0; i < 7; i++) {
			float sx = plPos.x - _vPos.x;
			float sz = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = _vPos;
			tmpPos.y = abs(height) + 1.0f;         // 地上から高さ1mより上
			BossBullet* bullet = NEW BossBullet();
			bullet->SetPos(tmpPos);                // 弾幕発生位置セット
			bullet->SetShotSpd(1.0f);              // 弾の移動速度セット
			bullet->SetAngle(deg + angleSide);     // 弾発射角度セット
			modeGame->_objServer.Add(bullet);      // 弾生成
			angleSide += 10.0f;                    // 発射角度を10°ずつずらす
			if (_shotHeight <= -12.0f) {
				height += 2.0f;    // 隣り合う弾と弾の高低差
			}
			else {
				height -= 2.0f;    // 隣り合う弾と弾の高低差
			}		
			if (abs(height) >= 12) {
				height += abs(height) - 12.0f;
				height *= -1.0f;
			}	
		}
		_shotHeight += 3.0f;  // 弾幕基準位置を3m毎上下に変化させる
		if (abs(_shotHeight) >= 11.0f) {
			_shotHeight *= -1.0f;
		}
	}
}

/**
 * 弾幕パターン6
 */
void Boss::ShotPattern6(){

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	VECTOR plPos = Player::GetInstance()->GetPos();
	if (_shotCnt % 48 == 0) {
		float angleSide = -10.0f;      // 弾3発中の両サイドの弾発射角度をずらす
		for (int i = 0; i < 3; i++) {
			float sx = plPos.x - _vPos.x;
			float sz = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = _vPos;
			tmpPos.y = 3.5f;
			BossBullet* bullet = NEW BossBullet();
			bullet->SetPos(tmpPos);                // 弾幕発生位置セット
			bullet->SetShotSpd(1.5f);              // 弾の移動速度セット
			bullet->SetAngle(deg + angleSide);     // 弾発射角度セット
			modeGame->_objServer.Add(bullet);      // 弾生成
			angleSide += 10.0f;                    // 発射角度を10°ずつずらす
		}
	}
}

void Boss::ShotPattern7() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 48==0) {
		VECTOR tmpPos = _vPos;
		tmpPos.y = _vPos.y + 12.0f;
		BossBomb* bomb = NEW BossBomb(tmpPos);
		modeGame->_objServer.Add(bomb);
	}
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
//	if (_stateDown) {
	if (_state == STATE::DOWN) {
		_mlsDownFlag = false;	   // マルチロックオンシステムによるダウンフラグ解除
		_downTime--;               // ダウン時間カウント
		if (_downTime < 0) {
			_downTime = 0;         // ダウン時間リセット
//			_stateDown = false;    // ダウン状態解除
			_state = STATE::RETURN;
			_bulletNum = 0;        // 弾の数リセット
			_shield = CHARA_DATA->_boss.maxShield;  // シールド値全回復
		}
	}

	if (_shield > 0) {
		return;
	}
	// ダウン
//	if (!_stateDown) {
	if (_state == STATE::NORMAL) {
		PlaySoundMem(gSound._se["down"], DX_PLAYTYPE_BACK);
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
				_bulletNum++;   // ダウン直前に出現していた弾の数をカウント
			}
			int plEnergy = Player::GetInstance()->GetEnergy();            // プレイヤーのエネルギー情報取得
			_downTime = MIN_DOWN_TIME + plEnergy / 20 + _bulletNum;       // ダウン時間計算
//			_stateDown = true;                                            // ダウン状態にする
			_state = STATE::DOWN;
		}
	}
}

/**
 * フレーム処理：計算
 */
void Boss::Process(){

	// カメラの状態を取得
	int camState = Camera::GetInstance()->GetCameraState();

	STATE oldState = _state;

	// ゲームクリア処理
	if (_gameClearFlag) {
		_gameClearCnt--;
		if (_gameClearCnt == 0) {
			ModeGameClear* modeGameClear = new ModeGameClear();
			ModeServer::GetInstance()->Add(modeGameClear, 2, "clear");
		}
	}
	// ヒットポイントゼロでゲームクリアフラグを立てる
	if (_hitpoint <= 0) {
		_hitpoint = 0;
		_gameClearFlag = true;
	}



	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos1.y = _vPos.y + ADD_POS_Y;   // y座標(高さ)のみ加算
	_capsulePos2 = _vPos;
	_capsulePos2.y = _vPos.y + ADD_POS_Y;   // y座標(高さ)のみ加算

	if (_state == STATE::RETURN) {
		if (_playTime == _totalTime) {
			_state = STATE::NORMAL;
		}
	}

	if (_state == STATE::NORMAL) {

		// 弾幕攻撃処理
		if (_shield > 0) {
			// マルチロックオンシステム発動中は弾の発射速度を遅くする
			if (camState == Camera::STATE::MLS_LOCK) {
				_mlsCnt++;
				if (_mlsCnt % 100 == 0) {
					ShotPatternSwitch();
				}
			}
			// 通常時
			else {
				_mlsCnt = 0;
				ShotPatternSwitch();
			}
		}

		{  // 仮実装：プレイヤーがいる方向にボスの正面を向ける
			VECTOR plPos = Player::GetInstance()->GetPos();
			float sx = plPos.x - _vPos.x;
			float sz = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;           // 制御しやすいように一度ラジアン単位を度単位に変換			
			float plAngle = (-deg - 90.0f) / 180.0f * DX_PI_F;  // 90度分のずれを補正し、ラジアン単位に戻す
			// 角速度を加え、プレイヤーがいる位置にゆっくりとボスの正面を向ける
			if (plAngle > _vDir.y) {
				_vDir.y += ROT_SPD;
			}
			else {
				_vDir.y -= ROT_SPD;
			}
//			_vDir.y = (-deg - 90.0f) / 180.0f * DX_PI_F;   
		}
	}
	// プレイヤーの弾との当たり判定、ダメージ処理
	{
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER_BULLET) {  
				if (IsHitLineSegment(*(*itr), 10.0f) == true) {
					if (_shield > 0) {
						_hitpoint -= CHARA_DATA->_shotDmgHP;
    					_shield -= CHARA_DATA->_shotDmgSld;
//						_shield -= 200;
						modeGame->_objServer.Del(*itr);
					}
					else {
						_shield = 0;
						_hitpoint -= CHARA_DATA->_shotDmg;
						modeGame->_objServer.Del(*itr);
					}
				}
			}		
		}
	}
	// フェーズ切替
	FhaseChange();
	// ダウン処理
	StateDown();

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
//			_attachIndex = MV1AttachAnim(_mh, MV1GetAnimIndex(_mh, "wait"), -1, FALSE);
			_attachIndex = -1;
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
 * フレーム処理：描画
 */
void Boss::Render(){

	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetPosition(_mh, _vPos);

	MV1SetRotationXYZ(_mh, _vDir);
	MV1DrawModel(_mh);

#if 1
	int y = 750;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Boss:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos     = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP　    = %d", _hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ｼｰﾙﾄﾞ値 = %d", _shield);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  出現している弾の数 = %d", _bulletNum);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ダウン時間 = %d", _downTime);   y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ｼｮｯﾄﾊﾟﾀｰﾝ = %d", _shotPattern); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  フェーズ = %d", _phase); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  状態 = %d", _state); y += size;
	DrawCapsule3D(_capsulePos1, _capsulePos2, 10.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}

/**
 * プレイヤーに弾き返された弾によるダメージ処理
 */
void Boss::Damage() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	PlaySoundMem(gSound._se["hit"], DX_PLAYTYPE_BACK);
	// シールドがあるとき
	if (_shield > 0) {  
		_hitpoint -= CHARA_DATA->_repelDmgHP;
		_shield -= CHARA_DATA->_repelDmgSld;
		if (_shield <= 0) {
			_shield = 0;
			_mlsDownFlag = true;  // プレイヤーに弾き返された弾でシールドが破壊されるとtrue
		}
	}
	// シールドがないとき
	else {            
		_hitpoint -= CHARA_DATA->_repelDmg;
	}
}

/**
 * プレイヤーから受けたダメージ量計算
 */
void Boss::AttackDamage(){

	PlaySoundMem(gSound._se["hit_boss"], DX_PLAYTYPE_BACK);
	int dmgHP = Player::GetInstance()->GetNowDmgHP();
	int dmgSld = Player::GetInstance()->GetNowDmgSld();
	int dmgNorm = Player::GetInstance()->GetNowDmgNorm();
	// シールドがあるとき
	if (_shield > 0) { 
		_hitpoint -= dmgHP;
		_shield -= dmgSld;
		if (_shield <= 0) {
			_shield = 0;
		}
	}
	// シールドがないとき
	else {            
		_hitpoint -= dmgNorm;
//		_hitpoint -= 500;
	}
}