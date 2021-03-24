/**
 * @file   ShotPattern.cpp
 * @brief  弾幕パターン処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#include "ShotPattern.h"
#include "ModeGame.h"
#include "BossBullet.h"
#include "BossAimShot.h"
#include "BossBomb.h"
#include "Laser.h"

 /**
  * 弾幕パターン切替処理
  */
void ShotPattern::ShotPatternSwitch(Boss* boss) {

	// フェーズ毎で発生する弾幕パターンを3セットランダムで変化させる
	if (boss->_shotCnt % PATTERN_CHANGE_CNT == 0) {
		boss->PlayAttackVoiceChange();       // 声データ再生
		boss->_shotCnt = 0;                  // カウントリセット
		boss->_shotPattern = rand() % 3 + 1; // 3パターンをランダムで決定
	}

	// フェーズ毎の弾幕パターンセット
	switch (boss->_phase) {
		// 初期フェーズ
	case 0:
		if (boss->_shotPattern <= 2) {
			ShotPattern1and2(boss);
		}
		else {
			ShotPattern3(boss);
		}
		break;
		// フェーズ1
	case 1:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern6(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
		}
		break;
		// フェーズ2
	case 2:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern7(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
			ShotPattern6(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		break;
		// フェーズ3
	case 3:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern6(boss);
			LaserAttack2(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		break;
		// フェーズ4
	case 4:
		if (boss->_shotPattern == 1) {
			ShotPattern3(boss);
			ShotPattern7(boss);
			LaserAttack2(boss);
		}
		if (boss->_shotPattern == 2) {
			ShotPattern4_1(boss);
			ShotPattern4_2(boss);
			ShotPattern6(boss);
			LaserAttack2(boss);
		}
		if (boss->_shotPattern == 3) {
			ShotPattern5(boss);
			ShotPattern6(boss);
			LaserAttack1_1(boss);
			LaserAttack1_2(boss);
		}
		break;
	}

	boss->_shotCnt++;
}

/**
 * 弾幕パターン1&2
 */
void ShotPattern::ShotPattern1and2(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (boss->_shotCnt % 17 == 0 && boss->_shotCnt != 1) {
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, boss->_shotAngle);
			modeGame->_objServer.Add(bullet); // 弾生成
			boss->_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}
	}
	else {
		if (boss->_shotPattern == 1) {
			boss->_shotAngle += 2.0f;   // 毎フレーム発射角度を2°ずらす
		}
		else if (boss->_shotPattern == 2) {
			boss->_shotAngle -= 2.0f;   // 毎フレーム発射角度を2°ずらす
		}
	}
}

/**
 * 弾幕パターン3
 */
void ShotPattern::ShotPattern3(Boss* boss) {

	boss->_reverseCnt--;
	if (boss->_reverseCnt <= 0) {
		boss->_reverseCnt = SHOT_REVERSE_CNT;
		boss->_setRotAngle *= -1.0f;
	}

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (boss->_shotCnt % 9 == 0) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 4.5f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.3f, boss->_shotAngle);
			modeGame->_objServer.Add(bullet); // 弾生成
			boss->_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}

	}
	else {
		boss->_shotAngle += boss->_setRotAngle;
	}
}

/**
 * 弾幕パターン4-1
 */
void ShotPattern::ShotPattern4_1(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (boss->_shotCnt % 26 == 0) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 3.5f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, boss->_shotAngle);
			modeGame->_objServer.Add(bullet); // 弾生成
			boss->_shotAngle += 45.0f;              // 弾発射角度を45°ずつずらす
		}
	}
	else {
		boss->_shotAngle += 2.0f;    // 毎フレーム発射角度を2°ずらす
	}
}

/**
 * 弾幕パターン4-2
 */
void ShotPattern::ShotPattern4_2(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (boss->_shotCnt % 26 == 13) {
		// 同時に8発弾を発射する
		for (int i = 0; i < 8; i++) {
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos.x = boss->_vPos.x + cos(boss->_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			tmpPos.y = 5.0f;
			tmpPos.z = boss->_vPos.z + sin(boss->_shotAngle1 / 180.0f * DX_PI_F) * SHOT_DISTANCE;
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.2f, boss->_shotAngle1);
			modeGame->_objServer.Add(bullet); // 弾生成
			boss->_shotAngle1 += 45.0f;             // 弾発射角度を45°ずつずらす
		}
	}
	else {
		boss->_shotAngle1 -= 2.0f;    // 毎フレーム発射角度を2°ずらす
	}
}

/**
 * 弾幕パターン5
 */
void ShotPattern::ShotPattern5(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	// プレイヤー位置取得
	VECTOR plPos = Player::GetInstance()->GetPos();

	// 同時に7発弾を発射する
	if (boss->_shotCnt % 8 == 0) {
		float angleSide = -30.0f;
		float height = boss->_shotHeight;
		for (int i = 0; i < 7; i++) {
			float sx = plPos.x - boss->_vPos.x;
			float sz = plPos.z - boss->_vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = boss->_vPos;
			tmpPos.y = abs(height) + 1.0f;         // 地上から高さ1mより上
			BossBullet* bullet = NEW BossBullet(tmpPos, 1.0f, deg + angleSide);
			modeGame->_objServer.Add(bullet);      // 弾生成
			angleSide += 10.0f;                    // 発射角度を10°ずつずらす
			if (boss->_shotHeight <= -12.0f) {
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
		boss->_shotHeight += 3.0f;  // 弾幕基準位置を3m毎上下に変化させる
		if (abs(boss->_shotHeight) >= 11.0f) {
			boss->_shotHeight *= -1.0f;
		}
	}
}

/**
 * 弾幕パターン6
 */
void ShotPattern::ShotPattern6(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	VECTOR plPos = Player::GetInstance()->GetPos();
	if (boss->_shotCnt % 48 == 0) {
		float angleSide = -10.0f;      // 弾3発中の両サイドの弾発射角度をずらす
		for (int i = 0; i < 3; i++) {
			float sx = plPos.x - boss->_vPos.x;
			float sz = plPos.z - boss->_vPos.z;
			float rad = atan2(sz, sx);
			float deg = rad * 180.0f / DX_PI_F;
			VECTOR tmpPos = { 0.0f,0.0f,0.0f };
			tmpPos = boss->_vPos;
			tmpPos.y = 3.5f;
			BossAimShot* bossAimShot = NEW BossAimShot(tmpPos, 1.5f, deg + angleSide);
			modeGame->_objServer.Add(bossAimShot);      // 弾生成
			angleSide += 10.0f;                    // 発射角度を10°ずつずらす
		}
	}
}

/**
 * 弾幕パターン7
 */
void ShotPattern::ShotPattern7(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (boss->_shotCnt % 48 == 0) {
		VECTOR tmpPos = boss->_vPos;
		tmpPos.y = boss->_vPos.y + 12.0f;
		BossBomb* bomb = NEW BossBomb(tmpPos);
		modeGame->_objServer.Add(bomb);
	}
}

/**
 * レーザー攻撃1-1
 */
void ShotPattern::LaserAttack1_1(Boss* boss) {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 0.0f;
	if (boss->_shotCnt == 0) {
		VECTOR tmpPos = boss->_vPos;
		tmpPos.x = boss->_vPos.x + cos(0.0f / 180.0f * DX_PI_F) * SHOT_DISTANCE;
		tmpPos.y = 4.5f;
		tmpPos.z = boss->_vPos.z + sin(0.0f / 180.0f * DX_PI_F) * SHOT_DISTANCE;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
		modeGame->_objServer.Add(laser);

	}
}

/**
 * レーザー攻撃1-2
 */
void ShotPattern::LaserAttack1_2(Boss* boss) {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 180.0f;
	if (boss->_shotCnt == 0) {
		VECTOR tmpPos = boss->_vPos;
		tmpPos.x = boss->_vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
		tmpPos.y = 4.5f;
		tmpPos.z = boss->_vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
		Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, -2.0f);
		modeGame->_objServer.Add(laser);

	}
}

/**
 * レーザー攻撃2
 */
void ShotPattern::LaserAttack2(Boss* boss) {
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	float laserAngle = 45.0f;
	if (boss->_shotCnt == 0) {
		// 同時に4本のレーザーを生成
		for (int i = 0; i < 4; i++) {
			VECTOR tmpPos = boss->_vPos;
			tmpPos.x = boss->_vPos.x + cos(0.0f / 180.0f * DX_PI_F) * 10.0f;
			tmpPos.y = 4.5f;
			tmpPos.z = boss->_vPos.z + sin(0.0f / 180.0f * DX_PI_F) * 10.0f;
			Laser* laser = NEW Laser(tmpPos, 10.0f, laserAngle, 1.0f);
			modeGame->_objServer.Add(laser);
			laserAngle += 90.0f;  // レーザー間の角度
		}
	}
}
