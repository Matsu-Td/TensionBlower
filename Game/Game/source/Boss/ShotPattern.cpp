/** 
 * @file   ShotPattern.cpp
 * @brief  弾幕パターン処理
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Boss.h"
#include "BossBullet.h"
#include "BossAimShot.h"
#include "BossBomb.h"
#include "../Effect/Laser.h"
#include "../Mode/ModeGame.h"

 /*
  * 弾幕パターン切替処理
  */
void Boss::ShotPatternSwitch() {

	// フェーズ毎で発生する弾幕パターンを3セットランダムで変化させる
	if (_shotCnt % PATTERN_CHANGE_CNT == 0) {
		PlayAttackVoiceChange();       // 声データ再生
		_shotCnt = 0;                  // カウントリセット
		_shotPattern = rand() % 3 + 1; // 3パターンをランダムで決定
	}

	// フェーズ毎の弾幕パターンセット
	switch (_phase) {
		// 初期フェーズ
	case 0:
		if (_shotPattern <= 2) {
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
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
		// フェーズ3
	case 3:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern6();
			LaserAttack2();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
		// フェーズ4
	case 4:
		if (_shotPattern == 1) {
			ShotPattern3();
			ShotPattern7();
			LaserAttack2();
		}
		if (_shotPattern == 2) {
			ShotPattern4_1();
			ShotPattern4_2();
			ShotPattern6();
			LaserAttack2();
		}
		if (_shotPattern == 3) {
			ShotPattern5();
			ShotPattern6();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
	}

	_shotCnt++;
}

/*
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
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, _shotAngle);
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

/*
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
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.3f, _shotAngle);
			modeGame->_objServer.Add(bullet); // 弾生成
			_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}

	}
	else {
		_shotAngle += _setRotAngle;
	}
}

/*
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
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, _shotAngle);
			modeGame->_objServer.Add(bullet); // 弾生成
			_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}
	}
	else {
		_shotAngle += 2.0f;    // 毎フレーム発射角度を2°ずらす
	}
}

/*
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
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, _shotAngle1);
			modeGame->_objServer.Add(bullet); // 弾生成
			_shotAngle1 += 45.0f;             // 弾発射角度を45°ずつずらす
		}
	}
	else {
		_shotAngle1 -= 2.0f;    // 毎フレーム発射角度を2°ずらす
	}
}

/*
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
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, deg + angleSide);
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

/*
 * 弾幕パターン6
 */
void Boss::ShotPattern6() {

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
			BossAimShot* bossAimShot = NEW BossAimShot(tmpPos, 1.5f, deg + angleSide);
			modeGame->_objServer.Add(bossAimShot);      // 弾生成
			angleSide += 10.0f;                    // 発射角度を10°ずつずらす
		}
	}
}

/*
 * 弾幕パターン7
 */
void Boss::ShotPattern7() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 48 == 0) {
		VECTOR tmpPos = _vPos;
		tmpPos.y = _vPos.y + 12.0f;
		BossBomb* bomb = NEW BossBomb(tmpPos);
		modeGame->_objServer.Add(bomb);
	}
}

/*
 * レーザー攻撃1-1
 */
void Boss::LaserAttack1_1() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 0.0f;
	if (_shotCnt == 0) {
		VECTOR tmpPos = _vPos;
		tmpPos.x = _vPos.x + cos(0.0f / 180.0f * DX_PI_F) * SHOT_DISTANCE;
		tmpPos.y = 4.5f;
		tmpPos.z = _vPos.z + sin(0.0f / 180.0f * DX_PI_F) * SHOT_DISTANCE;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
		modeGame->_objServer.Add(laser);

	}
}

/*
 * レーザー攻撃1-2
 */
void Boss::LaserAttack1_2() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 180.0f;
	if (_shotCnt == 0) {
		VECTOR tmpPos = _vPos;
		tmpPos.x = _vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
		tmpPos.y = 4.5f;
		tmpPos.z = _vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, -2.0f);
		modeGame->_objServer.Add(laser);

	}
}

/*
 * レーザー攻撃2
 */
void Boss::LaserAttack2() {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 45.0f;
	if (_shotCnt == 0) {
		// 同時に4本のレーザーを生成
		for (int i = 0; i < 4; i++) {
			VECTOR tmpPos = _vPos;
			tmpPos.x = _vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = _vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
			Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
			modeGame->_objServer.Add(laser);
			laserAngle += 90.0f;  // レーザー間の角度
		}
	}
}