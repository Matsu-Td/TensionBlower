#include "Boss.h"
#include "ModeGame.h"
#include "ApplicationMain.h"
#include "Player.h"

Boss* Boss::_pInstance = NULL;

Boss::Boss()
{
	_pInstance = this;
	_mh = ResourceServer:: MV1LoadModel("res/model/仮データ/nasuidou.mv1");

	Initialize();
}

Boss::~Boss()
{
}

void Boss::ShotPattern1() 
{
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	if (_shotCnt % 17 == 0 && _shotCnt != 1) {  
		for (int i = 0; i < 8; i++) {
			VECTOR tmp = { 0.0f,0.0f,0.0f };
			tmp.x = _vPos.x + cos(_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			tmp.y = 3.5f;
			tmp.z = _vPos.z + sin(_shotAngle / 180.0f * DX_PI_F) * 10.0f;
			BossBullet* bullet = new BossBullet();
			bullet->SetPos(tmp);
			bullet->SetAngle(_shotAngle);
			modeGame->_objServer.Add(bullet);
			_shotAngle += 45.0f;
		}
	}
	else {
		_shotAngle += 2.f;
	}

}
void Boss::Initialize()
{
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));


	_vPos = VGet(0.0f, 10.0f, 0.0f);
//	_vDir = VGet(1, 0, 1);
	_attachIndex = 0;
	_totalTime = 0.0f;

	_playTime = 0.0f;
	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);

	_shotAngle = -90.0f;
	_shotCnt = 0;
	_mlsCnt = 0;

	_hitpoint = CHARA_DATA->_boss.maxHP;
	_shield = CHARA_DATA->_boss.maxShield;
	_bulletNum = 0;
	_stateDown = false;
	_mlsDownFlag = false;
	_downTime = 0;
}

void Boss::StateDown()
{
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));

	if (_stateDown) {
		_mlsDownFlag = false;  // MLSダウンフラグ解除
		_downTime--;           // ダウン時間カウント
		if (_downTime < 0) {
			_downTime = 0;         // ダウン時間リセット
			_stateDown = false;    // ダウン状態解除
			_bulletNum = 0;        // 弾の数リセット
			_shield = CHARA_DATA->_boss.maxShield;  // シールド値回復
		}
	}

	if (_shield <= 0) {
		if (!_stateDown) {
			
			for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
				if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::BOSS_BULLET) {
					_bulletNum++;   // ダウン直前に出現していた弾の数をカウント
				}
				int plEnergy = Player::GetInstance()->GetEnergy();
				_downTime = 180 + plEnergy / 20 + _bulletNum;       // ダウン時間計算
				_stateDown = true;  // ダウン状態にする
			}
		}
	}
	else {
		//_stateDown = false;
	}

}

void Boss::Process()
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	

	/*for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			(*itr)->GetPos()
		}
	}*/
//	_playTime++;
	if (_playTime >= _totalTime) {
		_playTime = 0.f;
	}

	int camState = Camera::GetInstance()->GetCameraState();

	_capsulePos1 = _vPos;
	_capsulePos2 = _vPos;

	/**
	* 弾幕攻撃処理
	*/
	if (_shield	 > 0) {
		if (camState == Camera::STATE::MLS_LOCK) {  // マルチロックシステム発動中は弾の発射速度を遅くする
			_mlsCnt++;
			if (_mlsCnt % 100 == 0) {
				_shotCnt++;
				ShotPattern1();
			}
		}
		else {
			_shotCnt++;
			_mlsCnt = 0;
			ShotPattern1();
		}
	}

	/**
	* ダウン処理
	*/
	StateDown();

	/**
	* プレイヤーの弾との当たり判定、ダメージ処理
	*/ 
	{
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
			if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER_BULLET) {  // ステージ
				if (IsHitLineSegment(*(*itr), 10.0f) == true) {
					if (_shield > 0) {
						_hitpoint -= CHARA_DATA->_shotDmgHP;
//						_shield -= CHARA_DATA->_shotDmgSld;
						_shield -= 100; // デバッグ用
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

void Boss::Render()
{
	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(5.0f, 5.0f, 5.0f));
	MV1SetPosition(_mh, _vPos);

	MV1SetRotationXYZ(_mh, VGet(0.f,-90.0f * DX_PI_F / 180.0f,0.f));
	MV1DrawModel(_mh);

#if 1
	int y = 550;
	int size = 24;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "Boss:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos     = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  HP　    = %d", _hitpoint); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ｼｰﾙﾄﾞ値 = %d", _shield);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  出現している弾の数 = %d", _bulletNum);  y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  ダウン時間 = %d", _downTime);  
	DrawCapsule3D(_capsulePos1, _capsulePos2, 10.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
#endif
}

void Boss::Damage() {   // MLSで弾き返された弾によるダメージ処理
	if (_shield > 0) {  // シールドがあるとき
		_hitpoint -= 10;
		_shield -= 200;
		if (_shield <= 0) {
			_shield = 0;
			_mlsDownFlag = true;  // MLSで弾き返された弾でシールドが破壊されるとtrue
		}
	}
	else {             // シールドがないとき
		_hitpoint -= 10;
	}
}