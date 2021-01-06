#include "PlayerBullet.h"
#include "Player.h"
#include "ApplicationMain.h"

PlayerBullet::PlayerBullet()
{
	_mh = MV1LoadModel("res/model/仮データ/karinotama.mv1");
	Initialize();
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

	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	int rt = dinput.Z;    // ゲームパッド「RT」
	
	VECTOR plPos = Player::GetInstance()->GetPos(); // プレイヤー座標取得
	VECTOR plDir = Player::GetInstance()->GetDir(); // プレイヤー正面角度取得

	float plAngle = atan2(plDir.z, plDir.x); // プレイヤー正面の方向角度
	float mvSpd = 4.f;   // 弾の速度


	if (rt < -50) {
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
};