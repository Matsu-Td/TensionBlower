#include "ApplicationMain.h"
#include "BulletBase.h"

BulletBase::BulletBase()
{
	_mh = 0;
	_vPos = VGet(0.0f, 0.0f, 0.0f);
	_scrnPos = VGet(0.0f, 0.0f, 0.0f);

	_vx = _vz = 0.0f;
	_shotCnt = 0;
	_angle = 0.0f;
	_r = 0.0f;
}

BulletBase::~BulletBase()
{

}

void BulletBase::Update()
{

}

void BulletBase::Render()
{
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);
}