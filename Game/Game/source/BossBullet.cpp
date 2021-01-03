#include "BossBullet.h"
#include "Boss.h"

//BossBullet* BossBullet::_pInstance = NULL;

BossBullet::BossBullet()
{
	//_pInstance = this;
	_mh = MV1LoadModel("res/model/âºÉfÅ[É^/Wolf/Wolf.mv1");
	Initialize();
}

BossBullet::~BossBullet()
{

}

void BossBullet::Initialize()
{

	_vPos = VGet(0.f, 5.f, 0.f);
	_angle = -90.f;
	_vAngle = -90.f;
	_bltSpd = 0.2f;
	_cnt = 0;
	_vx = _vz = 0.f;
	_pattern = 0;
}

void BossBullet::Shot()
{
	_cnt++;
	//for (int i = 0; i < 1000; i++) {
		if (_cnt <= 8) {
			EnterShot();
		
		}
	//}
		if (_cnt == 300) {
			EnterShot();
		}

	for (auto itr = _lsBlt.begin(); itr != _lsBlt.end();) {
		itr->_vx = cos(itr->_angle / 180.f * DX_PI_F) * itr->_bltSpd;
		itr->_vz = sin(itr->_angle / 180.f * DX_PI_F) * itr->_bltSpd;
		itr->_vPos.x += itr->_vx;
		itr->_vPos.z += itr->_vz;
		itr++;
	}
}

void BossBullet::EnterShot()
{
	BossBullet tmp;
	switch (_pattern) {
	case 0:
		
		tmp._vPos = this->_vPos;
		tmp._angle = this->_angle;
		_lsBlt.push_back(tmp);
		this->_angle += 45.f;
		break;
	}

}

void BossBullet::Process()
{
	 _scrnPos = ConvWorldPosToScreenPos(_vPos);
	 Shot();

}

void BossBullet::Render()
{
	
	for (auto itr = _lsBlt.begin(); itr != _lsBlt.end();) {
		MV1SetScale(_mh, VGet(0.08f, 0.08f, 0.08f));
		MV1SetPosition(_mh, itr->_vPos);
		MV1SetRotationXYZ(_mh, VGet(0.f, (-itr->_angle + 270.f) / 180.f * DX_PI_F, 0.f));
		MV1DrawModel(_mh);
		
		itr++;
	}

#if 1
	int y = 160;
	int size = 16;
	SetFontSize(size);
	DrawFormatString(0, 700, GetColor(255, 0, 0), "  screenPos    = %d", _lsBlt.size());
	DrawFormatString(0, y, GetColor(255, 0, 0), "BossBullet:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  screenPos    = (%5.2f, %5.2f, %5.2f)", _scrnPos.x, _scrnPos.y, _scrnPos.z);
	DrawBox(_scrnPos.x - 5.f, _scrnPos.y - 5.f, _scrnPos.x + 5, _scrnPos.y + 5.f, GetColor(255, 0, 0), TRUE);
#endif
}