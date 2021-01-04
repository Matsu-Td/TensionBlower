#include "BossBullet.h"
#include "Boss.h"
#include "ApplicationMain.h"
#include "Stage.h"
#include "Player.h"

BossBullet* BossBullet::_pInstance = NULL;

BossBullet::BossBullet()
{
	_pInstance = this;
	//_mh = MV1LoadModel("res/model/���f�[�^/Wolf/Wolf.mv1");
	_mh = MV1LoadModel("res/model/���f�[�^/karinotama.mv1");
	//_mhMap = MV1LoadModel("res/model/���f�[�^/stage_dummy02.mv1");
	//_mhPl = MV1LoadModel("res/model/���f�[�^/SDChar/SDChar.mv1");

	Initialize();
}

BossBullet::~BossBullet()
{
	_lsBlt.clear();
}

void BossBullet::Initialize()
{

	_vPos = VGet(0.f, 5.f, 0.f);
	
	_angle = -90.f;
	_setAngle = 45.f;
	_bltSpd = 1.2f;
	_shotCnt = 0;
	_vx = _vz = 0.f;
	_pattern = 0;
//	_vPos.x = cos(_angle / 180.f * DX_PI_F) * 20.f;
//	_vPos.z = sin(_angle / 180.f * DX_PI_F) * 20.f;
//	_vPos.y = 0.5f;
}

void BossBullet::Shot()
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	_shotCnt++;

	ShotStart();

	for (auto itr = _lsBlt.begin(); itr != _lsBlt.end();) {
		itr->_vx = cos(itr->_angle / 180.f * DX_PI_F) * itr->_bltSpd;
		itr->_vz = sin(itr->_angle / 180.f * DX_PI_F) * itr->_bltSpd;
		itr->_vPos.x += itr->_vx;
		itr->_vPos.z += itr->_vz;
		itr++;
	}
}

void BossBullet::ShotStart()
{
	BossBullet tmp;
	switch (_pattern) {
	case 0:
		if (_shotCnt % 5 == 0 && _shotCnt != 1) {
			for (int i = 0; i < 8; i++) {
				_vPos.x = cos(_angle / 180.f * DX_PI_F) * 10.f;
				_vPos.z = sin(_angle / 180.f * DX_PI_F) * 10.f;
				tmp._vPos = this->_vPos;
				tmp._angle = this->_angle;
				_lsBlt.push_back(tmp);
				this->_angle += _setAngle;
			}
			
		}
		this->_angle += 2.f;
		break;

	case 1:
		//BossBullet tmp;
		tmp._vPos = this->_vPos;
		tmp._angle = this->_angle;
		_lsBlt.push_back(tmp);
		this->_angle += _setAngle;
		break;
	}

}

void BossBullet::Process()
{
	int mhStg = Stage::GetInstance()->_mh;
	int mhpl = Player::GetInstance()->_mh;
	MV1SetupCollInfo(mhStg, -1, 16, 16, 16);
	MV1SetupCollInfo(mhpl, -1, 16, 16, 16);
	 for (auto itr = _lsBlt.begin(); itr != _lsBlt.end();) {
		 // �����蔻��p�J�v�Z�����
		 itr->_capsulePos1 = itr->_vPos;
		 itr->_capsulePos1.y = itr->_vPos.y + 2.0f;

		 itr->_capsulePos2 = itr->_vPos;
		 itr->_capsulePos2.y = itr->_vPos.y + 2.0f;
		 itr->_capsulePos2.z = itr->_vPos.z + 1.f;
		 
		 itr->_scrnPos = ConvWorldPosToScreenPos(itr->_vPos);

		 // �X�e�[�W�ɓ���������폜
		 itr->_hitPolyDimStg = MV1CollCheck_Capsule(mhStg, -1, itr->_capsulePos1, itr->_capsulePos2, 2.f);
		 itr->_hitPolyDimPl = MV1CollCheck_Capsule(mhpl, -1, itr->_capsulePos1, itr->_capsulePos2, 2.f);
		 if (itr->_hitPolyDimStg.HitNum >= 1) {
			 itr = _lsBlt.erase(itr);
		 }
		 else if (itr->_hitPolyDimPl.HitNum >= 1) {
			 itr = _lsBlt.erase(itr);
		 }
		 else {
			 itr++;
		 }

	 }

	 // �e�̔�������
	 Shot();
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
	
#if 1
	int y = 160;
	int size = 16;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "BossBullet:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  screenPos    = (%5.2f, %5.2f, %5.2f)", _scrnPos.x, _scrnPos.y, _scrnPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  �o�������e�̐�(size())  = %d", _lsBlt.size());
	
#endif
}