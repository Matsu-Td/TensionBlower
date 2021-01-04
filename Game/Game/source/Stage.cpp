#include "Stage.h"
#include "ApplicationMain.h"

Stage* Stage::_pInstance = NULL;

Stage::Stage()
{
	_pInstance = this;
	_mh = MV1LoadModel("res/model/âºÉfÅ[É^/stage_dummy02.mv1");
}

Stage::~Stage()
{

}

void Stage::Initialize()
{

}

void Stage::Process()
{

}

void Stage::Render()
{
#ifdef _DEBUG
	{
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
#endif

	MV1DrawModel(_mh);
}