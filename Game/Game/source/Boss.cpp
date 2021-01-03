#include "Boss.h"

Boss* Boss::_pInstance = NULL;

Boss::Boss()
{
	_pInstance = this;
	_mh = MV1LoadModel("res/model/‰¼ƒf[ƒ^/nasuidou.mv1");

	Initialize();
}

Boss::~Boss()
{
	
}

void Boss::Initialize()
{
	_vPos = VGet(0.f, 10.f, 0.f);
//	_vDir = VGet(1, 0, 1);
	_attachIndex = 0;
	_totalTime = 0.f;

	_playTime = 0.f;
	_attachIndex = MV1AttachAnim(_mh, 0, -1, FALSE);
	_totalTime = MV1GetAttachAnimTotalTime(_mh, _attachIndex);
}

void Boss::Process()
{
	_playTime++;
	if (_playTime >= _totalTime) {
		_playTime = 0.f;
	}
	_bsBullet.Process();
}

void Boss::Render()
{
	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(5.f, 5.f, 5.f));
	MV1SetPosition(_mh, _vPos);

	MV1SetRotationXYZ(_mh, VGet(0.f,-90.f * DX_PI_F / 180.f,0.f));
	MV1DrawModel(_mh);

	_bsBullet.Render();

}