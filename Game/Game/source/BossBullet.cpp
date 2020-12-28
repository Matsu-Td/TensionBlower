#include "BossBullet.h"

BossBullet* BossBullet::_pInstance = NULL;

BossBullet::BossBullet()
{
	_pInstance = this;
	_mh = MV1LoadModel("res/model/âºÉfÅ[É^/Wolf/Wolf.mv1");
	Initialize();
}

BossBullet::~BossBullet()
{

}

void BossBullet::Initialize()
{
	_vPos = VGet(30.f, 10.f, 0.f);
}

void BossBullet::Process()
{
	 _screenPos = ConvWorldPosToScreenPos(_vPos);
}

void BossBullet::Render()
{

	MV1SetScale(_mh, VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(_mh, _vPos);
	MV1DrawModel(_mh);

#if 1
	int y = 160;
	int size = 16;
	SetFontSize(size);
	DrawFormatString(0, y, GetColor(255, 0, 0), "BossBullet:"); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _vPos.x, _vPos.y, _vPos.z); y += size;
	DrawFormatString(0, y, GetColor(255, 0, 0), "  screenPos    = (%5.2f, %5.2f, %5.2f)", _screenPos.x, _screenPos.y, _screenPos.z);
	DrawBox(_screenPos.x - 5, _screenPos.y - 5, _screenPos.x + 5, _screenPos.y + 5, GetColor(255, 0, 0), TRUE);
#endif
}