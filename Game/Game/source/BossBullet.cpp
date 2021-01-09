#include "BossBullet.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"

//BossBullet* BossBullet::_pInstance = NULL;

BossBullet::BossBullet()
{
	//_pInstance = this;
	_mh = ResourceServer::MV1LoadModel("res/model/仮データ/karinotama.mv1");

	Initialize();
}

BossBullet::~BossBullet()
{
	_lsBlt.clear();
}

void BossBullet::Initialize()
{

	
	_shot._angle = -90.f;
	_setAngle = 45.f;
	_shotCnt = 0;
	_mlsCnt = 0;
	_shot._vx = _shot._vz = 0.f;
	_pattern = 0;
}

void BossBullet::Shot()
{
	
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	int camState = Camera::GetInstance()->GetCameraState();

	

	//if (key & PAD_INPUT_2) { 
		
	//}
	if(camState == Camera::STATE::MLS_LOCK){
		_mlsCnt++;
		_bltSpd = NOR_SPD * 0.1f; // マルチロックオンシステム中は速度0.1倍
		if (_mlsCnt % 10 == 0) {
			_shotCnt++;
			ShotStart();
		}
	}
	else {
		_bltSpd = NOR_SPD;   // 通常時の弾の速度
		_shotCnt++;
		ShotStart();
	}
	
	

	for (auto itr = _lsBlt.begin(); itr != _lsBlt.end();) {
		itr->_vx = cos(itr->_angle / 180.f * DX_PI_F) * _bltSpd;
		itr->_vz = sin(itr->_angle / 180.f * DX_PI_F) * _bltSpd;
		itr->_vPos.x += itr->_vx;
		itr->_vPos.z += itr->_vz;
		itr++;
	}
}

void BossBullet::ShotStart()
{
	//auto tmp = std::make_unique<BossBullet>();
	//BossBullet tmp;
	
//	switch (_pattern) {
//	case 0:
	VECTOR bsPos = Boss::GetInstance()->GetPos();
	_shot._vPos = bsPos;
	_shot._vPos.y = 3.5f;
		if (_shotCnt % 17 == 0 && _shotCnt != 1) {
			SHOT tmp;
		//if (_shotCnt== 1) {
			for (int i = 0; i < 8; i++) {

				_shot._vPos.x = bsPos.x + cos(_shot._angle / 180.f * DX_PI_F) * 10.f;
				_shot._vPos.z = bsPos.z + sin(_shot._angle / 180.f * DX_PI_F) * 10.f;
			    tmp._vPos = _shot._vPos;
		    	tmp._angle = _shot._angle;
				_lsBlt.push_back(tmp);
				_shot._angle += _setAngle;
			}
		}
		_shot._angle += 2.f;
//		break;

	//}
}

void BossBullet::Process()
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	int mhStg = Stage::GetInstance()->_mh;
	int mhpl = Player::GetInstance()->_mh;

	Shot();

	MV1SetupCollInfo(mhStg, -1, 16, 16, 16);
	MV1SetupCollInfo(mhpl, -1, 16, 16, 16);
	 for (auto itr = _lsBlt.begin(); itr != _lsBlt.end();) {
		 // 当たり判定用カプセル情報
		 itr->_capsulePos1 = itr->_vPos;
		 itr->_capsulePos1.y = itr->_vPos.y + 2.0f;

		 itr->_capsulePos2 = itr->_vPos;
		 itr->_capsulePos2.y = itr->_vPos.y + 2.0f;
		 itr->_capsulePos2.z = itr->_vPos.z + 1.f;
		 
		 itr->_scrnPos = ConvWorldPosToScreenPos(itr->_vPos);
		
		 // ステージに当たったら削除
		 _hitPolyDimStg = MV1CollCheck_Capsule(mhStg, -1, itr->_capsulePos1, itr->_capsulePos2, 2.f);
		_hitPolyDimPl = MV1CollCheck_Capsule(mhpl, -1, itr->_capsulePos1, itr->_capsulePos2, 2.f);
		if (_hitPolyDimStg.HitNum >= 1) {
			 itr = _lsBlt.erase(itr);
		 }
		 else if (_hitPolyDimPl.HitNum >= 1) {
			 itr = _lsBlt.erase(itr);
		 }
		 else {
			 itr++;
		 }
		 
	 }

	 if (trg & PAD_INPUT_7) { _pattern = 1; }
	 if (trg & PAD_INPUT_8) { _pattern = 0; }
	 // 弾の発生処理
	
	// MV1CollResultPolyDimTerminate(_hitPolyDimStg);
}

void BossBullet::Render()
{
	//MV1SetScale(_mh, VGet(0.08f, 0.08f, 0.08f));
	for (auto itr = _lsBlt.begin(); itr != _lsBlt.end();) {

		MV1SetPosition(_mh, itr->_vPos);
		MV1SetRotationXYZ(_mh, VGet(0.f, (-itr->_angle + 270.f) / 180.f * DX_PI_F, 0.f));
		MV1DrawModel(_mh);
		//DrawCapsule3D(itr->_capsulePos1,itr->_capsulePos2, 2.f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
		//DrawBox(itr->_scrnPos.x - 5.f, itr->_scrnPos.y - 5.f, itr->_scrnPos.x + 5, itr->_scrnPos.y + 5.f, GetColor(255, 0, 0), TRUE);
		itr++;
	}
	DrawFormatString(0, 500, GetColor(255, 0, 0), "  出現した弾の数(size())  = %d", _lsBlt.size());
#if 0
	int y = 160;
	int size = 16;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "BossBullet:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  screenPos    = (%5.2f, %5.2f, %5.2f)", _scrnPos.x, _scrnPos.y, _scrnPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  出現した弾の数(size())  = %d", _lsBlt.size());
	
#endif
}