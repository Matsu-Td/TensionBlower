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

using namespace tensionblower::boss;

/*
 * フェーズ変更処理
 */
void Boss::FhaseChange() {

	// フェーズ4へ移行
	if (_hitpoint <= PHASE_FOUR_HP) {
		_phaseNo = 4;
		return;
	}
	// フェーズ3へ移行
	if (_hitpoint <= PHASE_THREE_HP) {
		_phaseNo = 3;
		return;
	}
	// フェーズ2へ移行
	if (_hitpoint <= PHASE_TWO_HP) {
		_phaseNo = 2;
		return;
	}
	// フェーズ1へ移行
	if (_hitpoint <= PHASE_ONE_HP) {
		_phaseNo = 1;
		return;
	}
	// 初期フェーズ0
	_phaseNo = 0;
}

/*
 * 弾幕パターン切替処理
 */
void Boss::BarragePatternSwitch() {

	// フェーズ毎で発生する弾幕パターンを3セットランダムで変化させる
	if (_shotCnt % PATTERN_CHANGE_CNT == 0) {
		PlayAttackVoiceChange();       // 声データ再生
		_shotCnt = 0;                  // カウントリセット
		_patternRandom = rand() % 3 + 1; // 3パターンをランダムで決定
	}

	// フェーズ毎の弾幕パターンセット
	switch (_phaseNo) {
		// 初期フェーズ
	case 0:
		if (_patternRandom <= 2) {
			BarragePattern1and2();
		}
		else {
			BarragePattern3();
		}
		break;
		// フェーズ1
	case 1:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern6();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
		}
		break;
		// フェーズ2
	case 2:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern7();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
			BarragePattern6();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
		// フェーズ3
	case 3:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern6();
			LaserAttack2();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
		// フェーズ4
	case 4:
		if (_patternRandom == 1) {
			BarragePattern3();
			BarragePattern7();
			LaserAttack2();
		}
		if (_patternRandom == 2) {
			BarragePattern4_1();
			BarragePattern4_2();
			BarragePattern6();
			LaserAttack2();
		}
		if (_patternRandom == 3) {
			BarragePattern5();
			BarragePattern6();
			LaserAttack1_1();
			LaserAttack1_2();
		}
		break;
	}

	_shotCnt++;
}

/*
 * 弾幕の弾を生成する
 */
void Boss::ShotGeneration(float posY, float shotSpd, float shotAngle) {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame* > (::mode::ModeServer::GetInstance()->Get("game"));
	
	VECTOR tmpPos = { 0.0f,0.0f,0.0f };
	
	tmpPos.x = _vPos.x + cos(util::DegToRad(shotAngle)) * SHOT_DISTANCE;
	tmpPos.y = posY;
	tmpPos.z = _vPos.z + sin(util::DegToRad(shotAngle)) * SHOT_DISTANCE;

	BossBullet* bullet = NEW BossBullet(tmpPos, shotSpd, shotAngle);
	modeGame->_objServer.Add(bullet); // 弾生成
}

/*
 * レーザーを生成する
 */
void Boss::LaserGeneration(float laserAngle, float roteSpd) {

	mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
	
	VECTOR tmpPos = _vPos;
	
	tmpPos.x = _vPos.x + cos(util::DegToRad(0)) * SHOT_DISTANCE;
	tmpPos.y = LESER_POS_Y;
	tmpPos.z = _vPos.z + sin(util::DegToRad(0)) * SHOT_DISTANCE;

	effect::Laser* laser = NEW effect::Laser(tmpPos, SHOT_DISTANCE, laserAngle, roteSpd);
	modeGame->_objServer.Add(laser);
}

/*
 * 弾幕パターン1&2
 */
void Boss::BarragePattern1and2() {

	if (_shotCnt % 17 == 0 && _shotCnt != 1) {
		for (int i = 0; i < 8; i++) {
			ShotGeneration(4.5f, 1.0f, _shotAngle);  // 弾生成
			_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}
	}
	else {
		if (_patternRandom == 1) {
			_shotAngle += 2.0f;   // 毎フレーム発射角度を2°ずらす
		}
		else if (_patternRandom == 2) {
			_shotAngle -= 2.0f;   // 毎フレーム発射角度を2°ずらす
		}
	}
}

/*
 * 弾幕パターン3
 */
void Boss::BarragePattern3() {

	_reverseCnt--;
	if (_reverseCnt <= 0) {
		_reverseCnt = SHOT_REVERSE_CNT;
		_setRotAngle *= -1.0f;
	}

	if (_shotCnt % 9 == 0) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			ShotGeneration(4.5f, 1.3f, _shotAngle);  // 弾生成
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
void Boss::BarragePattern4_1() {

	if (_shotCnt % 26 == 0) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			ShotGeneration(3.5f, 1.2f, _shotAngle);  // 弾生成
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
void Boss::BarragePattern4_2() {

	if (_shotCnt % 26 == 13) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			ShotGeneration(5.0f, 1.2f, _shotAngleUp);  // 弾生成
			_shotAngleUp += 45.0f;             // 弾発射角度を45°ずつずらす
		}
	}
	else {
		_shotAngleUp -= 2.0f;    // 毎フレーム発射角度を2°ずらす
	}
}

/*
 * 弾幕パターン5
 */
void Boss::BarragePattern5() {

	mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();

	// プレイヤー位置取得
	VECTOR plPos = player::Player::GetInstance()->GetPos();

	// 同時に7発弾を発射する
	if (_shotCnt % 8 == 0) {
		float angleSide = -30.0f;
		float height = _shotHeight;
		
		for (int i = 0; i < 7; i++) {
			float sx  = plPos.x - _vPos.x;
			float sz  = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = util::RadToDeg(rad);
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			
			tmpPos = _vPos;
			tmpPos.y = abs(height) + 1.0f;         // 地上から高さ1mより上
			
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, deg + angleSide);
			modeGame->_objServer.Add(bullet);      // 弾生成
			angleSide += 10.0f;                    // 発射角度を10°ずつずらす
			
			if (_shotHeight <= -SHOT_Y_MAX) {
				height += 2.0f;    // 隣り合う弾と弾の高低差
			}
			else {
				height -= 2.0f;    // 隣り合う弾と弾の高低差
			}
			if (abs(height) >= static_cast<int>(SHOT_Y_MAX)) {
				height += abs(height) - SHOT_Y_MAX;
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
void Boss::BarragePattern6() {

	VECTOR plPos = player::Player::GetInstance()->GetPos();
	if (_shotCnt % 48 == 0) {
		float angleSide = -10.0f;      // 弾3発中の両サイドの弾発射角度をずらす
		for (int i = 0; i < 3; i++) {
			float sx  = plPos.x - _vPos.x;
			float sz  = plPos.z - _vPos.z;
			float rad = atan2(sz, sx);
			float deg = util::RadToDeg(rad);
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			
			tmpPos = _vPos;
			tmpPos.y = 3.5f;
			
			BossAimShot* bossAimShot = NEW BossAimShot(tmpPos, 1.5f, deg + angleSide);
			mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
			modeGame->_objServer.Add(bossAimShot); // 弾生成
			angleSide += 10.0f;                    // 発射角度を10°ずつずらす
		}
	}
}

/*
 * 弾幕パターン7
 */
void Boss::BarragePattern7() {

	if (_shotCnt % 48 == 0) {
		VECTOR tmpPos = _vPos;
		
		tmpPos.y = _vPos.y + 12.0f;
		
		BossBomb* bomb = NEW BossBomb(tmpPos);
		mode::ModeGame* modeGame = mode::ModeGame::GetModeGame();
		modeGame->_objServer.Add(bomb);
	}
}

/*
 * レーザー攻撃1-1
 */
void Boss::LaserAttack1_1() {

	float laserAngle = 0.0f;  // レーザーの発射角度、位置
	if (_shotCnt == 0) {
		LaserGeneration(laserAngle);
	}
}

/*
 * レーザー攻撃1-2
 */
void Boss::LaserAttack1_2() {

	float laserAngle = 180.0f;  // レーザーの発射角度、位置
	if (_shotCnt == 0) {
		LaserGeneration(laserAngle, -2.0f);
	}
}

/*
 * レーザー攻撃2
 */
void Boss::LaserAttack2() {

	float laserAngle = 45.0f;  // レーザーの発射角度、位置
	if (_shotCnt == 0) {
		// 同時に4本のレーザーを生成
		for (int i = 0; i < 4; i++) {
			LaserGeneration(laserAngle);
			laserAngle += 90.0f;  // レーザー間の角度
		}
	}
}