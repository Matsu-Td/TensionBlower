
#include "DxLib.h"
#include "ObjectBase.h"
#include "math.h"

ObjectBase::ObjectBase()
{
	//MV1SetupCollInfo(_mh, -1, 8, 8, 8);
	Init();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Init()
{
	_cut = 0;
}

void ObjectBase::Process()
{
	_cut++;
}

void ObjectBase::Render()
{

}

bool ObjectBase::IsHitStage(ObjectBase& obj)
{
	
	MV1_COLL_RESULT_POLY_DIM _hitPolyDim;
	_hitPolyDim = MV1CollCheck_Capsule(obj._mh, -1, _capsulePos1, _capsulePos2, 1.f);
	if (_hitPolyDim.HitNum >= 1) {
		return true;
	}

	return false;
}