
/**
 * @file  Boss.cpp
 * @brief ボス関連処理
 *
 * @date 2021-02-11
 */

#include "Boss.h"
#include "ModeGame.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "ModeGameClear.h"

Boss* Boss::_pInstance = NULL;

Boss::Boss(){

	_pInstance = this;
	_mh = MV1LoadModel("res/model/boss/Tboss_model_mm.mv1");
	_cgName = ResourceServer::LoadGraph("res/enemy_name.png");
	_cgFrame = ResourceServer::LoadGraph("res/enemy_status.png");
	_cgFrameBg = ResourceServer::LoadGraph("res/enemy_status_2.png");
	_cgShield = ResourceServer::LoadGraph("res/enemy_shield.png");
	for (int i = 0; i < 5; i++) {
		_cgHP[i] = ResourceServer::LoadGraph(_cgString[i]);
	}

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

	_playTime = 0.0f;
	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

	_shotPattern = 1;
	_shotAngle = -90.0f;
	_shotAngle1 = -90.0f;
	_shotCnt = 0;
	_mlsCnt = 0;
	_reverseCnt = 60;
	_setRotAngle = 1.0f;
	_upDown = 2.0f;
	_height = 0.0f;

	_hitpoint = CHARA_DATA->_boss.maxHP;
	_shield = CHARA_DATA->_boss.maxShield;
	_bulletNum = 0;
	_stateDown = false;
	_mlsDownFlag = false;
	_downTime = 0;

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
			tmpPos.y = 3.5f;
			tmpPos.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			BossBullet* bullet = NEW BossBullet();
			bullet->SetPos(tmpPos);
			bullet->SetShotSpd(1.0f);
			bullet->SetAngle(_shotAngle);
			modeGame->_objServer.Add(bullet);
			_shotAngle += 45.0f;
		}
	}
	else {
		if (_shotPattern == 1) {
			_shotAngle += 2.0f;
		}
		else if (_shotPattern == 2) {
			_shotAngle -= 2.0f;
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
			tmpPos.y = 3.5f;
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
			tmpPos.y = 2.5f;
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
		_shotAngle += 2.0f;
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
		_shotAngle1 -= 2.0f;
	}
}

/**
 * 弾幕パターン5
 */
void Boss::ShotPattern5() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	VECTOR plPos = Player::GetInstance()->GetPos();
	if (_shotCnt % 8 == 0) {
		float angleSide = -30.0f;
		float height =_height;
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
			if (_height <= -12.0f) {
				height += 2.0f;
			}
			else {
				height -= 2.0f;
			}		
			if (abs(height) >= 12) {
				height += abs(height) - 12.0f;
				height *= -1.0f;
			}	
		}
		_height += 3.0f;
		if (abs(_height) >= 11.0f) {
			_height *= -1.0f;
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
			bullet->SetPos(tmpPos);
			bullet->SetShotSpd(1.5f);
			bullet->SetAngle(deg + angleSide);
			modeGame->_objServer.Add(bullet);
			angleSide += 10.0f;
		}
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
	if (_stateDown) {
		_mlsDownFlag = false;	   // マルチロックオンシステムによるダウンフラグ解除
		_downTime--;               // ダウン時間カウント
		if (_downTime < 0) {
			_downTime = 0;         // ダウン時間リセット
			_stateDown = false;    // ダウン状態解除
			_bulletNum = 0;        // 弾の数リセット
			_shield = CHARA_DATA->_boss.maxShield;  // シールド値全回復
		}
	}

	if (_shield > 0) {
		return;
	}
	// ダウン
	if (!_stateDown) {
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
				_bulletNum++;   // ダウン直前に出現していた弾の数をカウント
			}
			int plEnergy = Player::GetInstance()->GetEnergy();            // プレイヤーのエネルギー情報取得
			_downTime = MIN_DOWN_TIME + plEnergy / 20 + _bulletNum;       // ダウン時間計算
			_stateDown = true;                                            // ダウン状態にする
		}
	}
	
}

/**
 * フレーム処理：計算
 */
void Boss::Process(){

	// カメラの状態を取得
	int camState = Camera::GetInstance()->GetCameraState();


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

	// 未実装：アニメーション処理
	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}

	// 当たり判定用カプセル
	_capsulePos1 = _vPos;
	_capsulePos1.y = _vPos.y + 3.0f;   // y座標(高さ)のみ加算
	_capsulePos2 = _vPos;
	_capsulePos2.y = _vPos.y + 3.0f;   // y座標(高さ)のみ加算

	// フェーズ切替
	FhaseChange();

	// 弾幕攻撃処理
	if (_shield	 > 0) {
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

	// ダウン処理
	StateDown();

	{  // プレイヤーがいる方向にボスの正面を向ける
		VECTOR plPos = Player::GetInstance()->GetPos();
		float sx = plPos.x - _vPos.x;
		float sz = plPos.z - _vPos.z;
		float rad = atan2(sz, sx);
		float deg = rad * 180.0f / DX_PI_F;           // 制御しやすいように一度ラジアン単位を度単位に変換
		_vDir.y = (-deg - 90.0f)/ 180.0f * DX_PI_F;   // 90度分のずれを補正し、ラジアン単位に戻す
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
}

/**
 * フレーム処理：描画
 */
void Boss::Render(){

	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetPosition(_mh, _vPos);

	MV1SetRotationXYZ(_mh, _vDir);
	MV1DrawModel(_mh);

	DrawGraph(1090, 30, _cgFrameBg, TRUE);

	if (_phase == 0) {
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[0], TRUE);
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[1], TRUE);
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[2], TRUE);
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[3], TRUE);
		DrawExtendGraph(1113 + 750 - (750 * (_hitpoint - 4000) / 1000), 45, 1853, 80, _cgHP[4], TRUE);
	}
	if (_phase == 1) {
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[0], TRUE);
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[1], TRUE);
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[2], TRUE);
		DrawExtendGraph(1113 + 750 - (750 * (_hitpoint - 3000) / 1000), 45, 1853, 80, _cgHP[3], TRUE);
	}
	if (_phase == 2) {
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[0], TRUE);
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[1], TRUE);
		DrawExtendGraph(1113 + 750 - (750 * (_hitpoint - 2000) / 1000), 45, 1853, 80, _cgHP[2], TRUE);
	}
	if (_phase == 3) {
		DrawExtendGraph(1113, 45, 1853, 80, _cgHP[0], TRUE);
		DrawExtendGraph(1113 + 750 - (750 * (_hitpoint - 1000) / 1000), 45, 1853, 80, _cgHP[1], TRUE);
	}
	if (_phase == 4) {
		DrawExtendGraph(1113 + 750 - (750 * _hitpoint / 1000), 45, 1853, 80, _cgHP[0], TRUE);
	}

	DrawExtendGraph(1124 + 738 - (738 *_shield / 1000), 90, 1862, 120, _cgShield, TRUE);
	DrawGraph(1090, 30, _cgFrame, TRUE);
	DrawGraph(1650, 130, _cgName, TRUE);

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
	DrawFormatString(0, y, GetColor(255, 0, 0), "  テスト = %f", _a);
	DrawCapsule3D(_capsulePos1, _capsulePos2, 10.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}

/**
 * プレイヤーに弾き返された弾によるダメージ処理
 */
void Boss::Damage() {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

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
	}
}