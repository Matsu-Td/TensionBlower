#include "PlayerBullet.h"
#include "Player.h"
#include "ApplicationMain.h"

PlayerBullet::PlayerBullet()
{
	_mh = MV1LoadModel("res/model/‰¼ƒf[ƒ^/karinotama.mv1");
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Initialize()
{
	_shotFlag = false;
}

void PlayerBullet::Process()
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	VECTOR plPos = Player::GetInstance()->GetPos();
	VECTOR plDir = Player::GetInstance()->GetDir();

	float plAngle = atan2(plDir.z, plDir.x);
	float mvSpd = 10.f;


	if (key & PAD_INPUT_2) {
		_shotFlag = true;
	}
	else {
		_shotFlag = false;
	}

	float vx, vz;
	if (_shotFlag) {
		vx = cos(_shotAngle) * mvSpd;
		vz = sin(_shotAngle) * mvSpd;
		_vPos.x += vx;
		_vPos.z += vz;
	}
	else {
		_vPos = plPos;
		_vPos.y = plPos.y + 2.f;
		_shotAngle = plAngle;
	}
}

void PlayerBullet::Render()
{
	if (_shotFlag) {
		MV1SetPosition(_mh, _vPos);
		MV1DrawModel(_mh);
	}
}