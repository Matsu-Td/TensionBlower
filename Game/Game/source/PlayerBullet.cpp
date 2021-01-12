#include "PlayerBullet.h"
#include "Player.h"
#include "ApplicationMain.h"
#include  "ModeGame.h"
#include "Stage.h"

PlayerBullet::PlayerBullet()
{
	_mh = ResourceServer::MV1LoadModel("res/model/���f�[�^/karinotama1.mv1");
	Initialize();
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Initialize()
{
	_shotFlag = false;
	_vPos = Player::GetInstance()->GetPos(); // �v���C���[�ʒu�擾
	 
	VECTOR plDir = Player::GetInstance()->GetDir(); // �v���C���[���ʊp�x�擾
	_shotAngle = atan2(plDir.z, plDir.x); // �v���C���[���ʂ̕����p�x
}

void PlayerBullet::Process()
{
	ObjectBase::Process();

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	DINPUT_JOYSTATE dinput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinput);
	int rt = dinput.Z;    // �Q�[���p�b�h�uRT�v
	
	VECTOR plPos = Player::GetInstance()->GetPos(); // �v���C���[�ʒu�擾
	VECTOR plDir = Player::GetInstance()->GetDir(); // �v���C���[���ʊp�x�擾
	int mhStg = Stage::GetInstance()->_mh;
	float plAngle = atan2(plDir.z, plDir.x); // �v���C���[���ʂ̕����p�x
	float mvSpd = 4.f;   // �e�̑��x

	float vx, vz;

	vx = cos(_shotAngle) * mvSpd;
	vz = sin(_shotAngle) * mvSpd;
	_vPos.x += vx;
	_vPos.y = plPos.y + 3.5f;
	_vPos.z += vz;

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		

}

void PlayerBullet::Render()
{
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);
};