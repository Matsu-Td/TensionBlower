#include "Boss.h"
#include "ModeGame.h"
#include "ApplicationMain.h"

Boss* Boss::_pInstance = NULL;

Boss::Boss()
{
	_pInstance = this;
	_mh = ResourceServer:: MV1LoadModel("res/model/‰¼ƒf[ƒ^/nasuidou.mv1");

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

	_shotAngle = -90.0f;
	_shotCnt = 0;
}

void Boss::Process()
{
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	
	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	/*for (auto itr = modeGame->_objServer.List()->begin(); itr != modeGame->_objServer.List()->end(); itr++) {
		if ((*itr)->GetType() == ObjectBase::OBJECTTYPE::PLAYER) {
			(*itr)->GetPos()
		}
	}*/
	_playTime++;
	if (_playTime >= _totalTime) {
		_playTime = 0.f;
	}

	_shotCnt++;
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
	//_bsBullet.Process();
	//_vPos.x += 0.1f;
}

void Boss::Render()
{
	MV1SetAttachAnimTime(_mh, _attachIndex, _playTime);
	MV1SetScale(_mh, VGet(5.f, 5.f, 5.f));
	MV1SetPosition(_mh, _vPos);

	MV1SetRotationXYZ(_mh, VGet(0.f,-90.f * DX_PI_F / 180.f,0.f));
	MV1DrawModel(_mh);

	//_bsBullet.Render();

}