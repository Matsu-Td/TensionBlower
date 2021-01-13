
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

bool ObjectBase::IsHitStage(ObjectBase& obj, float r)
{

	obj._hitPolyDim = MV1CollCheck_Capsule(obj._mh, -1, _capsulePos1, _capsulePos2, r);
	if (obj._hitPolyDim.HitNum >= 1) {
		return true;
	}

	return false;
}

bool ObjectBase::IsHitLineSegment(ObjectBase& obj, float r)
{
	float length = Segment_Segment_MinLength(obj._capsulePos1, obj._capsulePos2, _capsulePos1, _capsulePos2);

	if (length <= r) {
		return true;
	}
	
	return false;
}